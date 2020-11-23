#!/usr/bin/env python3

import re
from operator import add
from pyspark import SparkContext

inputFile = 'hdfs://localhost:9000/wordcount/word.txt'
outputFile = 'hdfs://localhost:9000/wordcount-out/spark-out'

strinfo = re.compile(r'[^a-zA-Z]+')

def f(line):
	line = line.strip()
	words = line.split()
	ret = []
	for word in words:
		word = strinfo.sub("", word)
		word = word.strip()
		if word != "":
			ret.append(word.lower())
	return ret

sc = SparkContext('local', 'wordcount')
text_file = sc.textFile(inputFile)

counts = text_file.flatMap(lambda line: f(line)).map(lambda word: (word, 1)).reduceByKey(add)
counts.saveAsTextFile(outputFile)
