#!/usr/bin/env python3
import sys, re
lines = sys.stdin.readlines()
count = 0
argv1 = sys.argv[1]
for line in lines:
    line = line.lower()
    words = re.split('[^a-zA-Z]', line)

    for i in words:
        if i == argv1:
            count += 1
print(f'{argv1} occurred {count} times')