#!/usr/bin/env python3
import sys
hash = {}
count = int(sys.argv[1])
try:
    while True:
        word = input()
        if not hash.get(word):
            hash[word] = 1
        else:
            hash[word] += 1
        if hash[word] == count:
            print(f"Snap: {word}")
            break
except:
    pass