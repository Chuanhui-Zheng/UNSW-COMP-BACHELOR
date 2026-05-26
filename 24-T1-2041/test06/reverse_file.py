#! /usr/bin/env python3
import sys
if (len(sys.argv) != 3):
    print("error")
    exit(1)
textfile = open(sys.argv[1], "r")
lines = textfile.readlines()
textfile.close()

output = open(sys.argv[2], "w")
output.writelines(reversed(lines))
output.close()
