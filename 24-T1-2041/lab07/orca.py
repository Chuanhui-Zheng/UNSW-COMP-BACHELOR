#! /usr/bin/env python3
import sys,re
sum = 0
for file in sys.argv[1:]:
    output = open(file)
    with open(file) as output:
        while True:
            sentence = output.readline()
            if sentence == '':
                break
            else:
                if str(re.search('[A-Z].*$', sentence).group(0)) == 'Orca':
                    num = re.search(' \d+ ', sentence)
                    num = int(re.search('\d+', num.group(0)).group(0))
                    sum += num
    output.close()
print(sum,"Orcas reported")