import random

MSL = 1  # 1 sec maximum lifetime
TIME_WAIT = 2  # 2 * MSL (maximum segment lifetime)
MSS = 1000

server_log = "Receiver_log.txt" #　
client_log = "Sender_log.txt" # 


# ISN = random.randint(0, 65536)
ISN = 999 # test ISN example # 
# ISN = 65520 # test ISN example # 


#util
IP_addr = "127.0.0.1" # 


DATA_NUM = 0   # 
ACK_NUM   = 1  # 
SYN_NUM   = 2  # 
FIN_NUM   = 3  # 
RESET_NUM = 4  # 