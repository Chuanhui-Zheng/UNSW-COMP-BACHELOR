#!/usr/bin/env python3
import sys

file=sys.argv[1]

file = open(file).readlines()
if len(file) == 0:
    sys.exit(0)
length = len(file)
ret_len = -1
if length % 2 == 1:
    ret_len = length//2
    print(file[ret_len], end='')
else:
    ret_len = length//2-1
    print(file[ret_len], end='')
    print(file[ret_len+1], end='')