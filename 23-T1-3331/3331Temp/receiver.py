from const import *
import socket, time ,sys
from utility import *
receiver_port = int(sys.argv[1])
sender_port = int(sys.argv[2])
FileReceived = sys.argv[3]
flp = float(sys.argv[4])
rlp = float(sys.argv[5])
receiver_log = open(server_log, 'w+')
assert 49152 <= sender_port <= 65535, "49152 <= sender_port <= 65535, please choose one number randomly"
assert 49152 <= receiver_port <= 65535, "49152 <= receiver_port <= 65535, please choose one number randomly"
assert sender_port != receiver_port, "sender_port is different from receiver_port"
assert 0 <= flp <= 1, "0<=flp<=1, please enter a suitable range"
assert 0 <= rlp <= 1, "0<=rlp<=1, please enter a suitable range"

receiver = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
receiver_addr = (IP_addr, receiver_port)
receiver.bind(receiver_addr)

receiver_start_time, Data_Seg_Drop, ACK_Seg_Drop =time.time(), 0, 0
drp_syn_time, drp_fin_time = 0, 0
data_seq_all_lst, data_no_repeat_dict = [], {}
sum = 0
loop = True
summary_dict = {'Amout_Data_No_Repeat' : 0,'Data_Seg_Received_All': 0,'Data_Seg_Received_Repeat' : 0,'Data_Seg_Drop' : 0, 'ACK_Seg_Drop' : 0,}
while loop: 
    if not loop:
        break
    seg, addr = receiver.recvfrom(1004)    
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
                loop = False
                break
        if type_int == FIN_NUM:
            drp_fin_time += 1    
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, FIN_NUM, seq_num_int))
            if drp_fin_time == 4:
                loop = False
                break
        continue
    if type_int == SYN_NUM:
        receiver_log.write(write_log('rcv', time.time() - receiver_start_time, SYN_NUM, seq_num_int))
        send_num = seq_num_int + 1
        if not imitate_loss(rlp):
            ack_seg = create_segment(ACK_NUM, send_num)
            receiver.sendto(ack_seg, addr)
            receiver_log.write(write_log('snd', time.time() - receiver_start_time, ACK_NUM, send_num))
        else:
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, ACK_NUM, send_num))
            summary_dict['ACK_Seg_Drop'] += 1
    elif type_int == FIN_NUM:
        receiver_log.write(write_log('rcv', time.time() - receiver_start_time, FIN_NUM, seq_num_int))
        send_num = seq_num_int + 1
        if not imitate_loss(rlp):
            ack_seg = create_segment(ACK_NUM, send_num)
            receiver.sendto(ack_seg, addr)
            receiver_log.write(write_log('snd', time.time() - receiver_start_time, ACK_NUM, send_num))
            time.sleep(2)
            loop = False
            break
        else:
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, ACK_NUM, send_num))
            summary_dict['ACK_Seg_Drop'] += 1        
    elif type_int == RESET_NUM:
        receiver_log.write(write_log('rcv', time.time() - receiver_start_time, RESET_NUM, seq_num_int))
        sys.exit(0)
    elif type_int == DATA_NUM:
        data_seq_all_lst.append(seq_num_int)
        receiver_log.write(write_log('rcv', time.time() - receiver_start_time, DATA_NUM, seq_num_int, data_message))
        summary_dict['Data_Seg_Received_All'] += 1
        send_num = seq_num_int + len(data_message)
        if seq_num_int not in data_no_repeat_dict.keys():
            data_no_repeat_dict[seq_num_int] = data_message
        if not imitate_loss(rlp):
            ack_seg = create_segment(ACK_NUM, send_num)
            receiver.sendto(ack_seg, addr)
            receiver_log.write(write_log('snd', time.time() - receiver_start_time, ACK_NUM,  send_num ))
        else:
            receiver_log.write(write_log('drp', time.time() - receiver_start_time, ACK_NUM,  send_num ))
            summary_dict['ACK_Seg_Drop'] += 1




summary_dict['Amout_Data_No_Repeat'],summary_dict['Data_Seg_Received_All'], summary_dict['Data_Seg_Received_Repeat'] =len(set(data_seq_all_lst)), len(data_seq_all_lst), len(data_seq_all_lst) - len(set(data_seq_all_lst))

data_no_repeat_seq_lst = list(set(data_seq_all_lst))

idx = 0
sum = 0
while idx < len(data_seq_all_lst):
    seq = data_seq_all_lst[idx]
    sum += len(data_no_repeat_dict[seq])
    idx += 1
summary_dict['Amout_Data_No_Repeat'] = sum


data_no_repeat_seq_lst_sorted = sorted(data_no_repeat_seq_lst)
with open(FileReceived, 'w+') as f:
    for seq in data_no_repeat_seq_lst_sorted:
        f.write(data_no_repeat_dict[seq])
f.close()
with open(FileReceived, 'r') as f:
    content = f.read()
receiver_log.write(f'\nNumber of ACK segments dropped: {summary_dict["ACK_Seg_Drop"]}')
receiver_log.write(f'\nAmount of (original) Data Received (in bytes): {len(content)}\nNumber of (original) Data Segments Received: {summary_dict["Data_Seg_Received_All"]}\nNumber of duplicate segments received (if any): {summary_dict["Data_Seg_Received_Repeat"]}\nNumber of Data segments dropped: {summary_dict["Data_Seg_Drop"]}')


receiver.close()    