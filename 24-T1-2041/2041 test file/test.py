#!/usr/bin/env python3
import sys
import re

with open(sys.argv[2]) as file:
    for line in file:
        if not re.search(r'\s',line.strip()):
            print(line.strip(),end='')
        elif len(line.strip())<=int(sys.argv[1]):
            print(line,end='')
        elif re.search(r'\s',line.strip()):
            rem_space=re.sub(r'\s+\S','\n',line.strip())