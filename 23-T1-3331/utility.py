import random,time
from const import ISN, MSS
def concatSegment (typee, seq_num, data=b''):
    assert len(typee) <= 2, f"type is 2 types, while it is {len(typee)} types "
    assert len(seq_num) <= 2, f"seq_num is 2 types, while it is {len(seq_num)} types"
    assert len(data) <= 1000, f"data <= 1000 types, while it is {len(data)} types"
    assert type(typee) == bytes, f"type is bytes type, while it is {type(typee)}"
    assert type(seq_num) == bytes, f"seq_num is bytes type, while it is {type(seq_num)}"
    assert type(data) == bytes, f"data is bytes type, while it is {type(data)}"
    return typee + seq_num + data

def parse_segment(segment):
    type_bytes, seq_num_bytes, data_bytes = segment[0:2], segment[2:4], segment[4:]
    type_int = int.from_bytes(type_bytes, byteorder='big')
    seq_num_int = int.from_bytes(seq_num_bytes, byteorder='big')
    data_message = data_bytes.decode('utf-8')
    return type_int, seq_num_int, data_message

def create_segment(type_num, seq_num, data_message = ''):
    hex_ack_type = (type_num).to_bytes(2, byteorder='big') # 2bytes
    hex_ack_seq = seq_num.to_bytes(2, byteorder='big') # 2bytes
    return concatSegment(hex_ack_type, hex_ack_seq, data_message.encode('utf-8'))

def imitate_loss(probability):
    return random.random() - probability <= 0

def write_log(snd_or_rcv, timey, type_num, seq_num, data_message=''):

    lst = ['DATA', 'ACK', 'SYN', 'FIN', 'RESET']
    length = 0
    if type_num == 0:
        length = len(data_message)
    return f'{snd_or_rcv:<4} {timey:<8.6f} \t{lst[type_num]:<6} {seq_num:>5} {length}\n'

def subtra(a,b):
    return a - b if a > b else a + 65535 - b 
    
