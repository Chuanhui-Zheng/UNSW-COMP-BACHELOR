#! /usr/bin/env python3
import sys
import urllib.request
import re
import bs4 as BeautifulSoup

b = False
html5 = "html5lib"
address = f"http://www.timetable.unsw.edu.au/2024/{sys.argv[1]}KENS.html"
request = urllib.request.urlopen(address)

list_1 = []
list_1 = BeautifulSoup.BeautifulSoup(request.read().decode(), html5).find_all('a')
list_2 = []

for i in list_1:
    find = re.findall(sys.argv[1], str(i))
    if find:
        b = not b
        new_line = r'\n'
        empty = ' '
        extra = re.sub(new_line, empty, i.text)
        if not b:
            list_2[-1] = list_2[-1] + (empty + extra)
        elif b:
            list_2.append(extra)

list_3 = sorted(set(list_2))
for i in list_3:
    ex_1 = r'\1 \2'
    ex_2 = r'.*=\"([A-Z]{4}[0-9]{4})\.html\">([^<]+)<.*'
    new = re.sub(ex_2, ex_1, i)
    print(new)