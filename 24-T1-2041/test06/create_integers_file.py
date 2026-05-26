#!/usr/bin/env python3
import sys
if(len(sys.argv) != 4):
    print("error")
    exit(1)
begin = int(sys.argv[1])
end = int(sys.argv[2])
output = open(sys.argv[3], "w")
while(begin <= end):
    output.write(str(begin)+'\n')
    begin += 1
output.close()