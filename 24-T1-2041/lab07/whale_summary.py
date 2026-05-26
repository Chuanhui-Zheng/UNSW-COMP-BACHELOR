#! /usr/bin/env python3
import sys,re
whale_dic={}
for file in sys.argv[1:]:
    output = open(file)
    with open(file) as output:
        while True:
            sentence = output.readline()
            if sentence == '':
                break
            else:
                key = re.search('[a-zA-Z].*$', sentence)
                key = str(key.group(0))
                key = key.lower()
                key = re.sub('  ', ' ', key)
                key = re.sub('  ', ' ', key)
                key = re.sub('  ', ' ', key)
                key = re.sub('  ', ' ', key)
                key = re.sub('  ', ' ', key)
                key = re.sub('  ', ' ', key)
                key = re.sub('s$', '', key)
                key = re.sub(' $', '', key)
                num = re.search(' [0-9]{1,} ', sentence)
                num = re.search('[0-9]{1,}', num.group(0))
                num = int(num.group(0))
                if (key not in whale_dic):
                    whale_dic.update({key : num})
                    whale_dic[key + '_num'] = 1
                else:
                    whale_dic[key] += num
                    whale_dic[key + '_num'] += 1

    output.close()
new_whale_dic = sorted(whale_dic.keys())
prev = key
for key in new_whale_dic:
    if key != prev + '_num':
        whale_pods = key + '_num'
        whale_pods = re.sub('_num_num$', '_num', whale_pods)
        pods = whale_dic[whale_pods]
        if whale_dic[key] != pods:
            print(key, 'observations:', pods, 'pods,', whale_dic[key], 'individuals')
            prev = key