'''
	dataProcessing.py：处理数据，将其分为训练集与测试集。
	Author: HeRaNO
'''

import sys
import imblearn
import numpy as np
import pandas as pd

from imblearn.over_sampling import SMOTE
from sklearn.datasets import make_regression
from sklearn.ensemble import RandomForestRegressor
from sklearn.model_selection import train_test_split

# Start reading data
df = pd.read_csv("rankingcard.csv", index_col = 0)
df.drop_duplicates(inplace = True)
df.index = range(df.shape[0])
# Reading data end

# Start filling null data

# Fill the null data in NumberOfDependents
df["NumberOfDependents"].fillna(int(df["NumberOfDependents"].mean()), inplace = True)

# Fill the null data in MonthlyIncome
def fillMonthlyIncome(df):
	process_df = df.iloc[:, [5, 0, 1, 2, 3, 4, 6, 7, 8, 9]]
	known = process_df[process_df.MonthlyIncome.notnull()].iloc[:, :].values
	unknown = process_df[process_df.MonthlyIncome.isnull()].iloc[:, :].values
	X = known[:, 1:]
	y = known[:, 0]
	rfr = RandomForestRegressor(random_state = 0, n_estimators = 200, max_depth = 3, n_jobs = -1)
	rfr.fit(X,y)
	predicted = rfr.predict(unknown[:, 1:]).round(0)
	df.loc[df.MonthlyIncome.isnull(), 'MonthlyIncome'] = predicted
	return df

df = fillMonthlyIncome(df)

# delete the outliers
df = df[df["age"] != 0]
df = df[df.loc[:,"NumberOfTimes90DaysLate"] < 90]
df.index = range(df.shape[0])

# Filling null data end

# Start SMOTE

X = df.iloc[:, 1:]
y = df.iloc[:, 0]
sm = SMOTE(random_state = 42)
X, y = sm.fit_sample(X, y)

n_sample_ = X.shape[0]

n_1_sample = pd.Series(y).value_counts()[1]
n_0_sample = pd.Series(y).value_counts()[0]

print('样本个数： {}; 1 占 {:.2%}; 0 占 {:.2%}'.format(n_sample_, n_1_sample / n_sample_, n_0_sample / n_sample_), file = sys.stderr)

# SMOTE end

# Start divide

X = pd.DataFrame(X)
y = pd.DataFrame(y)

X_train, X_vali, Y_train, Y_vali = train_test_split(X, y, test_size = 0.3, random_state = 420)
model_data = pd.concat([Y_train, X_train], axis = 1)
model_data.index = range(model_data.shape[0])
model_data.columns = df.columns

vali_data = pd.concat([Y_vali, X_vali], axis = 1)
vali_data.index = range(vali_data.shape[0])
vali_data.columns = df.columns

# Divide end

model_data.to_csv("model_data.csv")
vali_data.to_csv("vali_data.csv")

print("Data processing ended successfully.", file = sys.stderr)
