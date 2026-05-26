#!/usr/bin/env python3
import sys

hash = {}
for i in sys.argv[1:]:
    hash[i] = i
for i in hash:
    print(i, end=" ")
print()