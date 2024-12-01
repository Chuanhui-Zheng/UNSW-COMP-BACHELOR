from const import *
import socket, time, threading, sys, copy
from utility import *
sender_port  = int(sys.argv[1])
receiver_port = int(sys.argv[2]) 
FileToSend = sys.argv[3]
max_win = float(sys.argv[4])
rto =  float(sys.argv[5])
rto /= 1000
sender_log ,fileToSend = open(client_log, "w+"),open(FileToSend, "r")
send_all_message = fileToSend.read()
pkts = [send_all_message[i: i+ MSS] for i in range(0, len(send_all_message), MSS)]
N = len(pkts) # 
assert 49152 <= sender_port <= 65535, "49152 <= sender_port <= 65535, please choose one number randomly"
assert 49152 <= receiver_port <= 65535, "49152 <= receiver_port <= 65535, please choose one number randomly"
assert sender_port != receiver_port, "sender_port is different from receiver_port"
assert max_win >= 1000 and max_win % 1000 == 0, "max_win must be greater than 1000 and be multiple of 1000 "
assert rto >= 0, "rto must be an unsigned integer"

class SEQ():
    def __init__(self,seq):
        self.seq = seq
global left, righ
left, righ = 0, 0
sender = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
receiver_addr = (IP_addr, receiver_port)
sender.connect(receiver_addr)
summary_dict = {'Amout_Data_No_Repeat' : 0,'Data_Seg_Received_No_Repeat' : 0,'Data_Seg_Resent_Repeat' :0,'ACK_Seg_Received_Repeat' :0}
sender_start_time = time.time()
seq_num_int  = 0
max = copy.deepcopy(0)
window_data = [{'result': False,'send_index':0,'time_stamp':0,'data_len': 0,'ack_received':0} for i in range(N)]
def send(typ, seq, message = ''): 
    global max
    if typ == 'SYN':
        seg = create_segment(SYN_NUM, seq, message)
        num = SYN_NUM
    if typ == 'DATA':
        seg = create_segment(DATA_NUM, seq, message)
        num = DATA_NUM
        if max < s.seq:
            max = s.seq
    if typ == 'FIN':
        seg = create_segment(FIN_NUM, seq, message)
        num = FIN_NUM
    if typ == 'RESET':
        seg = create_segment(RESET_NUM, seq, message)
        num = RESET_NUM
    sender.sendto(seg, receiver_addr)
    sender_log.write(write_log('snd', time.time() - sender_start_time, num, seq, message)) 
program_end = False

def rece(): # ACK
    global seq_num_int
    try:
        while not program_end:
            response, _ = sender.recvfrom(1024)
            type_int, seq_num_int, data_message = parse_segment(response)
            sender_log.write(write_log('rcv', time.time() - sender_start_time, ACK_NUM, seq_num_int)) 
            if type_int == ACK_NUM:
                for i in range(left, righ):
                    if window_data[i]['send_index'] + window_data[i]['data_len'] == seq_num_int  :  
                        window_data[i]['result'] = True
                        window_data[i]['ack_received'] += 1
    except socket.error:
        pass
# send SYN
send('SYN', ISN)
first = False
last_time = time.time()
# receive-thread
rece_thread = threading.Thread(target = rece)
rece_thread.start()
# receive ACK

rece_ack = False
while not rece_ack:  
    if seq_num_int == ISN + 1:
        s = SEQ(ISN + 1)
        rece_ack = True
        break
    else:
        for i in range(3):
            time.sleep(rto)
            if seq_num_int == ISN + 1:
                s = SEQ(ISN + 1)
                rece_ack = True
                break
            else:
                send('SYN', ISN)
        break
if not rece_ack:
    send('RESET', ISN)
    sender.close()
# send DATA_SEG
window_size = max_win // MSS if max_win / MSS == max_win // MSS else  max_win // MSS + 1
while left < N:
    while left < righ and window_data[left]['result']: # mv lef
          left += 1
    if left == N:
        break
    while righ < N and righ - left < int(window_size) : # mv rig
        window_data[righ]['send_index'] = s.seq
        window_data[righ]['time_stamp'] = time.time()
        window_data[righ]['data_len'] = len(pkts[righ])
        send('DATA', s.seq, pkts[righ])
        s.seq += len(pkts[righ])
        righ += 1

    if not window_data[left]['result'] and time.time() - window_data[left]['time_stamp'] > rto: # ot
        se = window_data[left]['send_index']
        send('DATA', se, pkts[left])
        summary_dict['Data_Seg_Resent_Repeat'] += 1
    for i in range(left, righ): # fast
        if window_data[i]['ack_received'] == 3:
            se = window_data[i]['send_index']
            send('DATA', se, pkts[i])
    time.sleep(rto / 10)
se = window_data[-1]['send_index'] + window_data[-1]['data_len'] + 1
# send FIN
send('FIN', se)
# receive ACK
rece_fin = False
while not rece_fin:  
    if seq_num_int == se + 1:
        rece_fin = True
        break
    else:
        for i in range(3):
            time.sleep(rto)
            if seq_num_int == se + 1:
                rece_fin = True
                break
            else:
                send('FIN', se)
        break
if not rece_fin:
    send('RESET', se)

summary_dict['Amout_Data_No_Repeat'] = len(send_all_message)
summary_dict['Data_Seg_Sent_No_Repeat'] = N
sender_log.write(f'\nAmount of (original) Data Transferred (in bytes) (excluding retransmissions):{summary_dict["Amout_Data_No_Repeat"]}\nNumber of Data Segments Sent (excluding retransmissions): {summary_dict["Data_Seg_Sent_No_Repeat"]}\nNumber of Retransmitted Data Segments: {summary_dict["Data_Seg_Resent_Repeat"]}\nNumber of Duplicate Acknowledgements received : {summary_dict["ACK_Seg_Received_Repeat"]}')

sender.close()