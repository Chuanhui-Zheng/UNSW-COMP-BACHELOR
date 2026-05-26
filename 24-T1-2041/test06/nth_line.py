#!/usr/bin/env python3
import sys
if(len(sys.argv) != 3):
    print("error")
    exit(1)
n = int(sys.argv[1])
with open(sys.argv[2], 'r') as file:
    lines = file.readlines()
    num_line = len(lines)
    if (num_line < n):
        exit(1)
print(lines[n-1], end="")
file.close()