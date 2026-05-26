#! /usr/bin/env python3
import sys,re
count = sys.argv[1]
count_begin = 0
count_line = 0
list_1 = list()
try:
    while True:
        a = input()
        a = a.lower()
        a = re.sub(' ', '', a, 1000)
        if a not in list_1:
            list_1.append(a)
            count_begin += 1
        count_line += 1

        if count_begin == int(count):
            break
    print(f'{count_begin} distinct lines seen after {count_line} lines read.')
except:
    print(f'End of input reached after {count_line} lines read - {count} different lines not seen.')
