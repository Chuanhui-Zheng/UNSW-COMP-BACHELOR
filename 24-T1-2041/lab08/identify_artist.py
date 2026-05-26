#!/usr/bin/env python3
import sys
import re
import glob
import math

for song in sys.argv[1:]:
    
	dict1 = {}
	dict2= {}
	singer = {}
	content = open(song, "r")
    
	for line in content:
		line = line.lower()
		line = line.rstrip()
		for word in re.split(r'[^a-z]+', line):
			if word != "":
				if word in dict1:
					dict1[word] += 1
				else:
					dict1[word] = 1
					dict2[word] = 0

	for musicfile in sorted(glob.glob("lyrics/*.txt")):
		total = 0
		for key in dict2:
			dict2[key]=0
			content = open(musicfile,"r")
			name = re.sub("lyrics/","",musicfile)
			name = re.sub(".txt","",name)
			name = re.sub("_"," ",name)
		for line in content:
			line = line.lower()
			all = re.findall("[A-Za-z]+",line)
			total += len(all)

			for key in dict1:
				reg= r"\b"+re.escape(key)+r"\b"
				array = re.findall(reg,line)
				dict2[key] += len(array)
		result = 0
		for key in dict1:
			result += dict1[key]*math.log(float(dict2[key]+1)/float(total))
		singer[name] = result
	val = max(singer, key=singer.get)
	print(song + " most resembles the work of "+ val + " (log-probability="+"{:.1f}".format(singer[val])+")")