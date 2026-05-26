#!/usr/bin/python3
import sys,re
import time
argv1 = sys.argv[1]
ret_list = []

flag_quit = 0
flag_print = 0
flag_delete = 0
flag_sub = 0
sub_words = ''
origin_words = ''
flag_sub_g = 1
ret_sub_count = -1
sub_count = -1
sub_address = ''
switch_sub = 0
# 检查是否为 'q' 命令
count = -1
flag_stop = 0
args = []
argv_print = ""
argv_delete = ""
argv_delete_begin_area = ""
argv_delete_end_area = ""
argv_print_begin_area = ""
argv_print_end_area = ""

argv_quit = ""
delete_switch = 0
print_switch = 0
flag_f = 0
argv_sub_begin_area = ""
argv_sub_end_area = ""
if argv1 == '-n':
    flag_stop = 1
    argv1 = sys.argv[2]

args = []

if argv1 == '-f':
    flag_f = 1
    argv1 = sys.argv[2]
if flag_f == 1:
    for line in open(argv1, 'r').readlines():
        line = line.strip()

        args.append(line)
else:
    argv1 = re.sub('#.*', '', argv1)
    if re.search(';', argv1) is not None:
        partitions = argv1.split(';')
        
        args.append(partitions[0])
        args.append(partitions[1])
    elif re.search('\n', argv1) is not None:
        partitions = argv1.split('\n')
        
        args.append(partitions[0])
        args.append(partitions[1])
    else:
        args.append(argv1)

for argv in args:
    argv = re.sub('\s', '', argv)
    argv = re.sub('#.*', '', argv)
    if re.search('q$', argv) is not None:
        flag_quit = 1
        if re.search('/', argv) is None:
            count = 0
        argv = re.sub('/', '', argv)
        argv = re.sub('q', '', argv)
        argv_quit = argv
    if re.search('d$', argv) is not None:
        flag_delete = 1
        if re.search('/', argv) is None:
            count = 0
        
        argv = re.sub('d', '', argv)
        argv_delete = argv
        if re.search(',', argv_delete) is not None:
            argv_delete_begin_area = argv_delete.split(',')[0]
            if re.search('/', argv_delete_begin_area) is not None:
                count = 0
            argv_delete_end_area = argv_delete.split(',')[1]
            if re.search('/', argv_delete_end_area) is not None:
                count = 0
        argv_delete = re.sub('/', '', argv_delete)

    if re.search('p$', argv) is not None:
        flag_print = 1
        if re.search('/', argv) is None:
            count = 1
        argv = re.sub('p', '', argv)

        argv_print = argv
        
        if re.search(',', argv_print) is not None:
            argv_print_begin_area = argv_print.split(',')[0]
            if re.search('/', argv_print_begin_area) is not None:
                count = 0
            argv_print_end_area = argv_print.split(',')[1]
            if re.search('/', argv_print_end_area) is not None:
                count = 0
        argv_print = re.sub('/', '', argv_print)

        
    if re.search('^\d+s', argv) is not None or re.search('^[^\\s].*[^\\s]s', argv) is not None or re.search('^s[^\\s].*[^\\s].*[^\\s]', argv) is not None :
        
        if re.search('^\d+', argv) is not None:
            sub_count = 1
            ret_sub_count = int(re.search('^\d+', argv).group(0))
            argv = re.sub('^/d+', '', argv)
        flag_sub = 1


        if re.search('^[^\\s].*[^\\s]s', argv) is not None:
            sub_address = re.search('^[^\\s].*[^\\s]s', argv).group(0)
            argv = re.sub('[^\\s].*[^\\s]s', 's', argv)
            
            sub_address = re.sub('s$', '', sub_address)

            if re.search(',', sub_address) is not None:
                argv_sub_begin_area = sub_address.split(',')[0]

                argv_sub_end_area = sub_address.split(',')[1]

            else:

                sub_address = re.sub('/', '', sub_address)
                sub_address = re.sub('s', '', sub_address)
                #sub_address = re.sub('[^\\s]', '', sub_address)

            
        
        if re.search('g$', argv) is not None:
            flag_sub_g = sys.maxsize
        
        if re.search('s[^\\s].*[^\\s].*[^\\s]', argv) is not None:
            
            split_words = re.search('s[^\\s].*[^\\s].*[^\\s]', argv).group(0)
            split_words = re.sub('^s', '', split_words)
            
            split_flag = re.search('^[^\\s]', split_words).group(0)
            split_words = re.split(re.escape(split_flag), split_words)
            origin_words = split_words[1]
            sub_words = split_words[2]
        
intput_lines = []
if len(sys.argv) > 2 and re.search('.txt', sys.argv[2]) is not None:

    for file_name in sys.argv[2:]:
        if re.search('.txt', file_name) is not None:
            file = open(file_name, 'r')
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                intput_lines.append(line)
else:
    start_time = time.time()
    for line in sys.stdin:
        if time.time() - start_time >= 2:
            break
        line = line.strip()
        intput_lines.append(line)

first_time_print = 0
for line in intput_lines:
    if flag_sub == 1 and origin_words != '' and re.search(origin_words, line) is not None:
        if argv_sub_begin_area != "":
            if re.search('/', argv_sub_begin_area) is not None:
                tmp_argv_sub_begin_area = re.sub('/', '', argv_sub_begin_area)
                if re.search(tmp_argv_sub_begin_area, line) is not None:
                    switch_sub = 1
        if ret_sub_count == -1:
            if sub_address != '':
                if re.search('/', argv_sub_begin_area) is not None:
                    if switch_sub == 1:
                        line = re.sub(origin_words, sub_words, line, count=flag_sub_g)
                else:
                    if re.search(sub_address, line) is not None:
                        line = re.sub(origin_words, sub_words, line, count=flag_sub_g)
            else:
                line = re.sub(origin_words, sub_words, line, count=flag_sub_g)
            
        else:
            if sub_count == ret_sub_count:
                line = re.sub(origin_words, sub_words, line, count=flag_sub_g)
            sub_count += 1
        if argv_sub_end_area != "":
            if re.search('/', argv_sub_end_area) is not None:
                tmp_argv_sub_end_area = re.sub('/', '', argv_sub_end_area)
                if re.search(tmp_argv_sub_end_area, line) is not None:
                    switch_sub = 0
    if count != -1:
        if argv_print == '' and flag_print == 1:
            print(line)
        
        if flag_print == 1 and str(count) == argv_print:

                print(line)
                if flag_stop == 1:
                    sys.exit(1)
        if flag_quit == 1 and argv_quit == str(count):
            if flag_delete == 1 and str(count) == argv_delete:
                print(line)
                count += 1
                continue
            else:
                sys.exit(1)
        count +=1

    if re.search('^\d+$', argv_delete_end_area) is not None:
        if str(count) == argv_delete_end_area and delete_switch != 0:
            delete_switch = 0
            continue
    else:
        tmp_argv_delete_end_area = re.sub('/', '', argv_delete_end_area)


        if argv_delete_end_area != "" and re.search(tmp_argv_delete_end_area, line) is not None and delete_switch != 0:
            delete_switch = 0
            continue
    if re.search('^\d+$', argv_delete_begin_area) is not None:
        if str(count) == argv_delete_begin_area:
            delete_switch = 1
        
    else:
        tmp_argv_delete_begin_area = re.sub('/', '', argv_delete_begin_area)

        if argv_delete_begin_area != "" and re.search(tmp_argv_delete_begin_area, line) is not None:
            delete_switch = 1



    
    if re.search('^\d+$', argv_print_begin_area) is not None:
        if str(count) == argv_print_begin_area:
            print_switch = 1
        
    else:
        tmp_argv_print_begin_area = re.sub('/', '', argv_print_begin_area)

        if argv_print_begin_area != "" and re.search(tmp_argv_print_begin_area, line) is not None:
            print_switch = 1
        if argv_print_begin_area != "" and re.search(tmp_argv_print_begin_area, line) is None and first_time_print != 0:
            print_switch = 0

    if print_switch == 1:
        print(line)

    if re.search('^\d+$', argv_print_end_area) is not None:
        #print(str(count), argv_print_end_area)
        if str(count) == argv_print_end_area and print_switch != 0:
            print_switch = 0
            first_time_print = 1
    else:
        
        tmp_argv_print_end_area = re.sub('/', '', argv_print_end_area)


        if argv_print_end_area != "" and re.search(tmp_argv_print_end_area, line) is not None and print_switch != 0:
            print_switch = 0
            first_time_print = 1
    
    if delete_switch == 1:
        continue
    if argv_delete == "$":
        if count == len(intput_lines):
            continue
    elif argv_delete != "" and re.search(argv_delete, line) is not None and flag_delete == 1:
        if flag_stop == 1:
            
            sys.exit(1)
        continue
    elif flag_delete == 1 and argv_delete == "":
        sys.exit(1)
    if flag_stop == 1 and flag_print == 1:

        if argv_print == "$":
            if count-1 == len(intput_lines):
                print(line)
            continue
        elif re.search(argv_print, line) is not None:
            print(line)
        continue
    print(line)

    if argv_print == "$":
        if count-1 == len(intput_lines):
            print(line)
        continue

    if count == -1:
        if flag_print == 1 and re.search(argv_print, line) is not None:
            print(line)
        if flag_quit == 1 and re.search(argv_quit, line) is not None:

            sys.exit(1)