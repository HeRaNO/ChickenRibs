'''
	check.py：检查 submission 与给的 gender_submission 的一致性。
	Author：HeRaNO
'''
import sys
import numpy as np
import pandas as pd

myDf = pd.read_csv('submission.csv', index_col = 0)
ans = pd.read_csv('data\\gender_submission.csv')

X = ans.Survived
Y = myDf.Survived

res = X + Y
cnt = 0

for i in res:
	if i == 1:
		cnt += 1

print(cnt, len(X))

