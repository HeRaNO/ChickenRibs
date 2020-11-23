#!/usr/bin/env python3
import re
import sys

strinfo = re.compile(r'[^a-zA-Z]+')

for line in sys.stdin:
	line = line.strip()
	words = line.split()
	for word in words:
		word = strinfo.sub("", word)
		word = word.strip()
		if word != "":
			print("%s\t1" % word.lower())
