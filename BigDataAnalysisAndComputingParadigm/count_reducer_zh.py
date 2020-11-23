#!/usr/bin/env python3
import sys

nowWord = None
nowCount = 0

for line in sys.stdin:
	line = line.strip()
	word, cnt = line.split('\t', 1)
	try:
		cnt = int(cnt)
	except ValueError:
		print('count: %s' % cnt, file = sys.stderr)
		continue
	if word == nowWord:
		nowCount += cnt
	else:
		if nowWord:
			print("%s\t%d" % (nowWord, nowCount))
		nowWord = word
		nowCount = cnt

if nowWord:
	print("%s\t%d" % (nowWord, nowCount))
