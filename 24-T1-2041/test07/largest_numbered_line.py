#!/usr/bin/env python3
import sys, re

max_num = 0
inputs = {}
try:
    while True:
        tmp_max = -1
        sentence = input()
        nums = re.findall('-?\d+\.?\d*e?\d*?', sentence)
        for i in nums:
            tmp_max = max(tmp_max, float(i))
            max_num = max(max_num, float(i))
        inputs[sentence] = tmp_max
except:
    for k, v in inputs.items():
        if v == max_num:
            print(k)