'''
	makeRankingCard.py：制作评分卡。
	Author: HeRaNO
'''

import sys
import imblearn
import numpy as np
import pandas as pd

from sklearn.linear_model import LogisticRegression as LR

# Read data start
model = pd.read_csv("model_data.csv", index_col = 0)
vali = pd.read_csv("vali_data.csv", index_col = 0)
# Read data end

# Start binning

def calcWOE(num_bins):
	columns = ["min", "max", "count_0", "count_1"]
	df = pd.DataFrame(num_bins, columns = columns)

	df["total"] = df.count_0 + df.count_1
	df["percentage"] = df.total / df.total.sum()
	df["bad_rate"] = df.count_1 / df.total
	df["goodpercent"] = df.count_0 / df.count_0.sum()
	df["badpercent"] = df.count_1 / df.count_1.sum()
	df["woe"] = np.log(df["goodpercent"] / df["badpercent"])
	return df

def calcIV(df):
	rate = df["goodpercent"] - df["badpercent"]
	iv = np.sum(rate * df.woe)
	return iv

def bestBin(DF, X, Y, n, q):
	pass
	'''
		自己写吧我写崩溃了
		大概的取值：
		RevolvingUtilizationOfUnsecuredLines：8
		age：11
		DebtRatio：11
		MonthlyIncome：9
		NumberOfOpenCreditLinesAndLoans：6
		其余均无法分箱，需要手动分
	'''

# 分箱应该得到一个 bins_of_col[] 数组，里面是分箱的分段点

# Binning end

# Modeling start

model_woe = pd.DataFrame(index = model_data.index)
for col in bins_of_col:
	model_woe[col] = pd.cut(model_data[col],bins_of_col[col]).map(woeall[col])

model_woe["SeriousDlqin2yrs"] = model_data["SeriousDlqin2yrs"]

vali_woe = pd.DataFrame(index = vali_data.index)
for col in bins_of_col:
	vali_woe[col] = pd.cut(vali_data[col],bins_of_col[col]).map(woeall[col])

vali_woe["SeriousDlqin2yrs"] = vali_data["SeriousDlqin2yrs"]

vali_X = vali_woe.iloc[:,:-1]
vali_y = vali_woe.iloc[:,-1]

X = model_woe.iloc[:,:-1]
y = model_woe.iloc[:,-1]

lr = LR().fit(X, y)
lr.score(vali_X, vali_y)

# Modeling end

# Make card start

B = 20 / np.log(2)
A = 600 + B * np.log(1 / 60)

with open("score.csv", "w") as fdata:
      fdata.write("base_score,{}\n".format(base_score))

for i, col in enumerate(X.columns):
	score = woeall[col] * (-B * lr.coef_[0][i])
	score.name = "Score"
	score.index.name = col
	score.to_csv(file, header = True, mode = "a")
# Make card end
