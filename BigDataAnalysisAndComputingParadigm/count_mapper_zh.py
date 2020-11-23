#!/usr/bin/env python3
import re
import sys
import jieba

strinfo = re.compile(u"[^\u4e00-\u9fff]+")

for line in sys.stdin:
	line = line.strip()
	words = jieba.cut(line)
	for word in words:
		word = strinfo.sub("", word)
		word = word.strip()
		if word != "":
			print("%s\t1" % word)
