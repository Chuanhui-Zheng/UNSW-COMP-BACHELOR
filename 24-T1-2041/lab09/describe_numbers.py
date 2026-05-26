#! /usr/bin/env python3
import sys

list_1 = list()
list_2= list()
sum = 0
product = 1
count = 0

for i in sys.argv[1:]:
    if int(i) not in list_1:
        list_2.append(int(i))
    list_1.append(int(i))
    sum += int(i)
    product *= int(i)
    count += 1
minimum = int(sys.argv[1])
maximum = int(sys.argv[1])
unique = 0

for i in list_2:
    if i < minimum:
        minimum = i
    if i > maximum:
        maximum = i
    unique += 1

list_3 = sorted(list_1)
median = list_3[count // 2]
if sum % count == 0:
    mean = sum // count
else:
    mean = sum / count
mode = sys.argv[1]
max_mode = 0
for i in list_2:
    count_mode = 0
    for j in list_3:
        if i == j:
            count_mode += 1
    if count_mode > max_mode:
        max_mode = count_mode
        mode = i

print(f'count={count}')
print(f'unique={unique}')
print(f'minimum={minimum}')
print(f'maximum={maximum}')
print(f'mean={mean}')
print(f'median={median}')
print(f'mode={mode}')
print(f'sum={sum}')
print(f'product={product}')