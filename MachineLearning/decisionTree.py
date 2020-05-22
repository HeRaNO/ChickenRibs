'''
	decisionTree.py：预测隐形眼镜类型的决策树模型
	Author：HeRaNO
'''
# coding: utf-8

# import os # For debug
import sys
import math
import random # shuffle
from functools import reduce

from graphviz import Digraph

ATRNUM = 4 # Constant, the number of attribute

class Node():
	def __init__(self, atr, val, lch, rch):
		self.atr = atr # Attribute ID
		self.val = val # Divide value
		self.lch = lch # Left child
		self.rch = rch # Right child

def readData():
	with open('lenses.txt', 'r') as f:
		lines = f.readlines()
	df = [l.strip().split('\t') for l in lines]
	labels = ['age', 'impairment', 'astigmatric', 'tearRate']
	dic = []
	rev = []
	result = {}
	for i in range(ATRNUM):
		dic.append({})
		rev.append([])
		t = list(set([x[i] for x in df]))
		cnt = 0
		for x in t:
			dic[i][x] = cnt
			rev[i].append(x)
			cnt += 1
	t = list(set([x[-1] for x in df]))
	cnt = 0
	for x in t:
		result[x] = cnt
		cnt += 1
	return df, labels, dic, result, rev

def log2(x):
	return math.log(x, 2) if x > 0 else 0

def calcShannonEntropy(df, res):
	if not df:
		return 0
	cnt = [0, 0, 0]
	l = 0
	for i in df:
		cnt[res[i[-1]]] += 1
		l += 1
	p = map(lambda x : float(x) / l, cnt)
	return reduce(lambda x, y : x - y * log2(y), p, 0)

def divideByAtr(df, atr, val, dic):
	eq = []
	ne = []
	for i in df:
		if dic[i[atr]] != val:
			ne.append(i)
		else:
			eq.append(i)
	return eq, ne

def calcDivideByAtr(df, atr, cnt, dic, res):
	bestH = 1E9
	bestVal = 0
	for i in range(cnt):
		eq, ne = divideByAtr(df, atr, i, dic)
		Heq = calcShannonEntropy(eq, res)
		Hne = calcShannonEntropy(ne, res)
		H = float(len(eq)) / cnt * Heq + float(len(ne)) / cnt * Hne
		if bestH > H:
			bestH, bestVal = H, i
	return bestH, bestVal

def buildDecisionTreeID3(x, df, dic, res):
	H = calcShannonEntropy(df, res)
	'''
	print(H, file = sys.stderr)
	os.system("pause")
	'''
	if H == 0:
		if df:
			x.atr = df[0][-1]
		return
	bestAtr = 0
	bestVal = 0
	bestH = 1E9
	for atr in range(ATRNUM):
		nowH, nowVal = calcDivideByAtr(df, atr, len(dic[atr]), dic[atr], res)
		# print(nowH, nowVal, file = sys.stderr)
		if bestH > nowH:
			bestH, bestAtr, bestVal = nowH, atr, nowVal
	'''
	print(bestAtr, bestVal, file = sys.stderr)
	os.system("pause")
	'''
	x.atr, x.val = bestAtr, bestVal
	x.lch = Node(0, 0, 0, 0)
	x.rch = Node(0, 0, 0, 0)
	equal, notEqual = divideByAtr(df, bestAtr, bestVal, dic[bestAtr])
	'''
	print(equal, file = sys.stderr)
	print(notEqual, file = sys.stderr)
	os.system("pause")
	'''
	buildDecisionTreeID3(x.lch, equal, dic, res)
	buildDecisionTreeID3(x.rch, notEqual, dic, res)

def classifyData(x, df, dic):
	if type(x.atr) == str:
		print("Except: ", df[-1], "found: ", x.atr)
		return df[-1] == x.atr
	if dic[x.atr][df[x.atr]] == x.val:
		return classifyData(x.lch, df, dic)
	else:
		return classifyData(x.rch, df, dic)

def testTree(rt, df, dic):
	okCnt = 0
	for i in df:
		if classifyData(rt, i, dic):
			okCnt += 1
	print(okCnt, "/", len(df))
	print("check ok")

def drawTree(x, g, labels, rev, meta):
	g.node(name = labels[x.atr] + meta)
	if type(x.lch.atr) == str:
		g.node(name = x.lch.atr, color = "green")
		g.edge(labels[x.atr] + meta, x.lch.atr, rev[x.atr][x.val])
	else:
		drawTree(x.lch, g, labels, rev, meta + " ")
		g.edge(labels[x.atr] + meta, labels[x.lch.atr] + meta + " ", rev[x.atr][x.val])
	if type(x.rch.atr) == str:
		g.node(name = x.rch.atr, color = "green")
		g.edge(labels[x.atr] + meta, x.rch.atr, "else")
	else:
		drawTree(x.rch, g, labels, rev, meta + "  ")
		g.edge(labels[x.atr] + meta, labels[x.rch.atr] + meta + "  ", "else")

print("load data start", file = sys.stderr)
df, labels, dic, result, rev = readData()
print("load data ok", file = sys.stderr)

random.shuffle(df)
traindata = df[:int(len(df) * 0.8)]
testdata = df[int(len(df) * 0.8):]

rt = Node(0, 0, 0, 0)
print("Build tree start", file = sys.stderr)
buildDecisionTreeID3(rt, traindata, dic, result)
print("Build tree ok", file = sys.stderr)

print("Test tree start", file = sys.stderr)
testTree(rt, testdata, dic)
print("Test tree ok", file = sys.stderr)

print("Save tree start", file = sys.stderr)
g = Digraph("决策树")
drawTree(rt, g, labels, rev, "")
g.view()
print("Save tree ok", file = sys.stderr)
