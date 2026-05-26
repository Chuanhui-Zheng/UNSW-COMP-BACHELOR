#!/usr/bin/env python3

import sys
import re

list=set()
for line in sys.stdin:
    if re.search(r'\|M',line):
        name=line.strip().split('|')[2].strip().split(',')[0]
        list.add(name)
for i in sorted(list):
    print(i)