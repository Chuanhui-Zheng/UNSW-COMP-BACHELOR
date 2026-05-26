#! /usr/bin/env python3
import sys,subprocess,re

list = []
ret = subprocess.run(["curl", "--location", "--silent", f"http://www.timetable.unsw.edu.au/2024/{sys.argv[1]}KENS.html"],  capture_output=True, text=True)
for i in ret.stdout.split("\n"):
    expression = '.*=\"([A-Z]{4}[0-9]{4})\.html\">([^<]+)<.*'
    first = re.findall(sys.argv[1], i)
    second = re.findall(expression, i)
    if first and second:
        list.append(i)
list = list[1::2]
third = sorted((set(list)))
for i in third:
    ex = r'\1 \2'
    extra = r'.*=\"([A-Z]{4}[0-9]{4})\.html\">([^<]+)<.*'
    new = re.sub(extra, ex, i)
    print(new)