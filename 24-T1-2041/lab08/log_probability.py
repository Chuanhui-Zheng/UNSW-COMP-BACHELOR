#!/usr/bin/env python3

import sys, re
import glob, math

list1 = []
list2 = []
for i in sys.argv[1:]:
    list2.append(i)

for file in glob.glob('lyrics/*.txt'):
    list1.append(file)
list1.sort()


for file in list1:
    
    intotal = 0
    file_name = re.sub('lyrics/', '', file)
    file_name = re.sub('.txt', '', file_name)
    file_name = re.sub('_', ' ', file_name)
    lines = open(file).readlines()
    
    total_freq = 0
    for argv in list2:
        count = 1
        count_word = 0
        for line in lines:
            words = re.split('[^a-zA-Z]', line)
            for i in words:
                if i != '':
                    count_word += 1
                i = i.lower()
                if i == argv:
                    count += 1
        frequency = count / count_word

        total_freq += math.log(frequency)

    print(f'{total_freq:10.5f} {file_name}')
