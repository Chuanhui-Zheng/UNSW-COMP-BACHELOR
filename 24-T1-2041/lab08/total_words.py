#!/usr/bin/env python3
import sys, re
lines = sys.stdin.readlines()
count = 0
for line in lines:
    words = re.split('[^a-zA-Z]', line)
    for i in words:
        if i != '':
            count += 1
print(count, 'words')