#!/usr/bin/env python3
import sys

list1 = []
lines = open(sys.argv[1]).readlines()
for line in lines:
    list1.append(line)
while True:
    count = 0
    if len(list1) == 0:
        break
    min_val = list1[count]
    while count < len(list1):
        if len(min_val) > len(list1[count]):
            min_val = list1[count]
        count += 1
    print(min_val, end='')
    list1.remove(min_val)
    list1.sort()

