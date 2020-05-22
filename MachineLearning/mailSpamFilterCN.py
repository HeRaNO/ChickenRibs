'''
	mailSpamFilterCN.py：用于中文垃圾邮件分类，采用 Naive Bayes 方法
	Author：HeRaNO
'''
# coding: utf-8

import re
import sys
import math

import jieba
import pandas as pd

def readContent(path):
	with open(path, 'r', encoding = 'gbk', errors = 'ignore') as f:
		l = f.readlines()
	l = filter(lambda line: line != '\n', l)
	return ''.join(''.join(l).strip().split())

def loadStopWords():
	with open('stop', 'r', encoding = 'gbk', errors = 'ignore') as f:
		l = f.readlines()
	return [i.strip() for i in l]

def loadData():
	dataset = pd.read_csv('index', sep = ' ', names = ['spam', 'path'])
	dataset.spam = dataset.spam.apply(lambda x: 1 if x == 'spam' else 0)
	dataset.path = dataset.path.apply(lambda x: x[1:])
	return dataset

def createDict(content, stop_list):
	content = re.findall(u'[\u4E00-\u9FD5]', content)
	content = ''.join(content)
	d = []
	div = jieba.cut(content)
	for word in div:
		if word != '' and word not in stop_list:
			d.append(word)
	return dict([(word, 1) for word in d])

def naiveBayesPrepare(df):
	dic = {}
	for words, spam in zip(df.words, df.spam):
		for w in words:
			dic.setdefault(w, {0: 0, 1: 0})
			dic[w][spam] += 1
	okCount = df.spam.value_counts()[0]
	spamCount = df.spam.value_counts()[1]
	return dic, okCount, spamCount

def naiveBayes(content, dic, spamCount, okCount):
	allCnt = spamCount + okCount
	words = content['words']
	Pok = math.log(float(okCount) / allCnt)
	Pspam = math.log(float(spamCount) / allCnt)
	for w in words:
		w = w.strip()
		dic.setdefault(w, {0: 0, 1: 0})
		ok = dic[w][0]
		spam = dic[w][1]
		Pok += math.log((float(ok) + 1) / (okCount + 2))
		Pspam += math.log((float(spam) + 1) / (spamCount + 2))
	isSpam = 1 if Pspam > Pok else 0
	return 1 if isSpam == content['spam'] else 0

print("load path and stop words start", file = sys.stderr)
df = loadData()
stop_list = loadStopWords()
print("load path and stop words ok", file = sys.stderr)

print("load content start", file = sys.stderr)
df['content'] = df.path.apply(lambda x: readContent(x))
print("load content ok", file = sys.stderr)

print("make dict start", file = sys.stderr)
df['words'] = df.content.apply(lambda x: createDict(x, stop_list))
print("make dict ok", file = sys.stderr)

trainset = df.loc[:len(df) * 0.8]
testset = df.loc[len(df) * 0.8:]

print("train start", file = sys.stderr)
wordDict, okCount, spamCount = naiveBayesPrepare(trainset)
print("okCount: ", okCount)
print("spamCount: ", spamCount)
print("train ok", file = sys.stderr)

print("predict start", file = sys.stderr)
pdt = testset.apply(lambda x: naiveBayes(x, wordDict, spamCount, okCount), axis = 1)
print("predict ok", file = sys.stderr)

result = 1 - float(pdt.value_counts().get(0, 0)) / pdt.value_counts().sum()

print("Accuracy: ", result)
