#!/usr/bin/python3

d = {1: '001', 2: '010', 3: 'Not found'}
# since 4 is not in keys, it'll print "Not found"
print(d.get(1, "001"))