#!/usr/bin/env python3
import sys, re
import glob

argv1 = sys.argv[1]
list1 = []
for file in glob.glob('lyrics/*.txt'):
    list1.append(file)
list1.sort()
for file in list1:
    count = 0
    intotal = 0
    file_name = re.sub('lyrics/', '', file)
    file_name = re.sub('.txt', '', file_name)
    file_name = re.sub('_', ' ', file_name)
    lines = open(file).readlines()
    count_word = 0
    for line in lines:
        words = re.split('[^a-zA-Z]', line)
        
        
        for i in words:

            if i != '':
                count_word += 1
            i = i.lower()
            if i == argv1:
                count += 1
    frequency = count / count_word

    print(f'{count:4}/{count_word:6} = {frequency:.9f} {file_name}')