#!/usr/bin/env python3
import sys

def if_vowel(ch):
    if ch == 'a' or ch == 'e' or ch == 'i' or ch == 'o' or ch == 'u' or ch == 'A' or ch == 'E' or ch == 'I' or ch == 'O' or ch == 'U':
        return True
    else:
        return False

list1 = []
for argv in sys.argv:
    if len(argv) < 3:
        continue
    count = 0
    while count+2 < len(argv):
        if if_vowel(argv[count]) and if_vowel(argv[count+1]) and if_vowel(argv[count+2]):
            list1.append(argv)
            break
        count += 1
for i in list1:
    print(i, end=' ')

print()