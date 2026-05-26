#! /usr/bin/env python3
import sys,re
file = sys.argv[2]
regex = sys.argv[1]
output = open(file, 'r')
while True:
    lines = output.readline()
    if lines == "":
        break
    if re.search(regex, lines) is not None:
        print(lines, end="")