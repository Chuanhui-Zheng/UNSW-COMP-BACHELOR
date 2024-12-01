from const import *
import socket, time ,sys, os, threading
from utility import *
receiver_port = int(sys.argv[1])
sender_port = int(sys.argv[2])
FileReceived = sys.argv[3]
flp = float(sys.argv[4])
rlp = float(sys.argv[5])
# sender_port, receiver_port, FileReceived, flp, rlp = 54321, 56789, "FileReceived.txt", 0.5, 0.5 # 
receiver_log = open(server_log, 'w+')
assert 49152 <= sender_port <= 65535, "49152 <= sender_port <= 65535, please choose one number randomly"
assert 49152 <= receiver_port <= 65535, "49152 <= receiver_port <= 65535, please choose one number randomly"
assert sender_port != receiver_port, "sender_port is different from receiver_port"
assert 0 <= flp <= 1, "0<=flp<=1, please enter a suitable range"
assert 0 <= rlp <= 1, "0<=rlp<=1, please enter a suitable range"
reset = False

receiver = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
receiver_addr = (IP_addr, receiver_port)
receiver.bind(receiver_addr)

receiver_start_time, Data_Seg_Drop, ACK_Seg_Drop =time.time(), 0, 0
drp_syn_time, drp_fin_time = 0, 0
drp_ack_of_syn_time = 0
data_seq_all_lst = []
loop = True
start_seq = 0
summary_dict = {'Amout_Data_No_Repeat' : 0,'Data_Seg_Received_All': 0,'Data_Seg_Received_Repeat' : 0,'Data_Seg_Drop' : 0, 'ACK_Seg_Drop' : 0,}
counter = -1
rece_buffer = 16 * 1000 # bytes
receive_dict = [{"counter":i, "seq":0, "data_len":0,"message":""} for i in range(rece_buffer // MSS)] # 16 sizes
        #                   [{counter : ,seq : ,data_len: },
        #                    {counter : ,seq : ,data_len: },
        #               ...                             ] 
first = True
while loop: 
    if not loop:
        break
    def RESETclose():
        receiver.close()
    try:
        seg, addr = receiver.recvfrom(1004)
    except socket.timeout:
        pass
    if first and not seg:
        receiver.settimeout(2 * MSL)
        first = False
    type_int = int.from_bytes(seg[0:2], byteorder='big')
    seq_num_int = int.from_bytes(seg[2:4], byteorder='big')
    data_message = seg[4:].decode('utf-8')
  
    if imitate_loss(flp):
        if type_int == DATA_NUM:
            summary_dict['Data_Seg_Drop'] += 1
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, DATA_NUM, seq_num_int))
        if type_int == SYN_NUM:
            drp_syn_time += 1
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, SYN_NUM, seq_num_int))
            
            if drp_syn_time == 4:
                receiver.settimeout(2 * MSL)
                break
        if type_int == FIN_NUM:
            drp_fin_time += 1    
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, FIN_NUM, seq_num_int))
            if drp_fin_time == 4:
                loop = False
                break
        continue

    # connect successfully
    if type_int == SYN_NUM:
        receiver_log.write(write_log('rcv', time.time() - receiver_start_time, SYN_NUM, seq_num_int))
        send_num = seq_num_int + 1
        start_seq = seq_num_int + 1
        if not imitate_loss(rlp):
            ack_seg = create_segment(ACK_NUM, send_num)
            receiver.sendto(ack_seg, addr)
            receiver_log.write(write_log('snd', time.time() - receiver_start_time, ACK_NUM, send_num))
        else:
            drp_syn_time += 1
            if drp_syn_time == 4:
                receiver.settimeout(2)
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, ACK_NUM, send_num))
            summary_dict['ACK_Seg_Drop'] += 1
    elif type_int == FIN_NUM:

        receiver_log.write(write_log('rcv', time.time() - receiver_start_time, FIN_NUM, seq_num_int))
        send_num = seq_num_int + 1
        if not imitate_loss(rlp):
                ack_seg = create_segment(ACK_NUM, send_num)
                receiver.sendto(ack_seg, addr)
                receiver_log.write(write_log('snd', time.time() - receiver_start_time, ACK_NUM, send_num))
                receiver.settimeout(0.1)                    
                break
        else:
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, ACK_NUM, send_num))
            summary_dict['ACK_Seg_Drop'] += 1        
    elif type_int == RESET_NUM:
        receiver_log.write(write_log('rcv', time.time() - receiver_start_time, RESET_NUM, seq_num_int))
        break
    elif type_int == DATA_NUM:
        # come
        data_seq_all_lst.append(seq_num_int)
        receiver_log.write(write_log('rcv', time.time() - receiver_start_time, DATA_NUM, seq_num_int, data_message))
        summary_dict['Data_Seg_Received_All'] += 1
        
        for i in range(len(receive_dict)):
            if  receive_dict[i]["seq"] == seq_num_int :
                summary_dict['Data_Seg_Received_Repeat'] += 1
            if (start_seq + receive_dict[i]["counter"] * 1000) % (2**16) == seq_num_int % 2**16:
                receive_dict[i]["message"] = data_message
                receive_dict[i]["data_len"] = len(data_message)
        # back
        if not imitate_loss(rlp):                
            send_num = (seq_num_int + len(data_message)) % 2**16
            ack_seg = create_segment(ACK_NUM, send_num)
            receiver.sendto(ack_seg, addr)
            receiver_log.write(write_log('snd', time.time() - receiver_start_time, ACK_NUM,  send_num ))
        else:
            send_num = (seq_num_int + len(data_message)) % 2**16
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, ACK_NUM,  send_num ))
            summary_dict['ACK_Seg_Drop'] += 1


with open(FileReceived, 'w+') as f:
    for i in range(len(receive_dict)):
        f.write(receive_dict[i]["message"])
f.close()
def dupData():
    if not receive_dict[0]["seq"]:
        return 0
    else:
        for i in range(len(summary_dict)):
            if receive_dict[i]["message"]:
                i += 1
            else:
                break
        return i - 1 
        
with open(FileReceived, 'r') as f2:
    content = f2.read()
receiver_log.write(f'\nAmount of (original) Data Received (in bytes) : {len(content)}')
receiver_log.write(f'\nNumber of (original) Data Segments Received : {summary_dict["Data_Seg_Received_All"]}')
receiver_log.write(f'\nNumber of duplicate  Data segments received (if any) : {dupData()} ')   
receiver_log.write(f'\nNumber of Data segments dropped : {summary_dict["Data_Seg_Drop"]} ')                   
receiver_log.write(f'\nNumber of ACK segments dropped : {summary_dict["ACK_Seg_Drop"]}')
receiver_log.close()
f2.close()

i = 0 


if receiver:
    receiver.close()
os._exit(0)   
