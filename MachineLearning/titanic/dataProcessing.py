'''
	dataProcessing.py：用于处理数据。
	Author：HeRaNO
'''

import re
import sys
import numpy as np
import pandas as pd
from sklearn.ensemble import RandomForestRegressor

def makeTitleDict():
	Title_Dict = {}
	Title_Dict.update(dict.fromkeys(['Capt', 'Col', 'Major'], 1))
	Title_Dict.update(dict.fromkeys(['Jonkheer', 'Sir', 'Countess', 'Lady', 'Don', 'Dona'], 2))
	Title_Dict.update(dict.fromkeys(['Dr', 'Rev'], 3))
	Title_Dict.update(dict.fromkeys(['Mme', 'Ms', 'Mrs'], 4))
	Title_Dict.update(dict.fromkeys(['Mlle', 'Miss'], 5))
	Title_Dict.update(dict.fromkeys(['Mr'], 6))
	Title_Dict.update(dict.fromkeys(['Master'], 7))
	return Title_Dict

def transFamSizToLable(x):
	if x >= 2 and x <= 4:
		return 0
	if x > 7:
		return 2
	return 1

def transAgeToLable(x):
	return (int(x) - 1) // 5 + 1

train = pd.read_csv('data\\train.csv')
test = pd.read_csv('data\\test.csv')
allDf = pd.concat([train, test], ignore_index = True)
Title_Dict = makeTitleDict()

allDf.drop(['PassengerId', 'Ticket', 'Fare', 'Cabin'], axis = 1, inplace = True)

allDf['Title'] = allDf.Name.str.extract(r' ([A-Za-z]+)\.', expand=False)
allDf['Title'] = allDf['Title'].map(Title_Dict)
allDf.drop(['Name'], axis = 1, inplace = True)

allDf['Embarked'] = allDf['Embarked'].fillna('S')
allDf['FamilySize'] = allDf['SibSp'] + allDf['Parch'] + 1
allDf['FamilyLable'] = allDf['FamilySize'].apply(transFamSizToLable)
allDf['Sex'] = allDf['Sex'].map({'male': 0, 'female': 1})
allDf['Embarked'] = allDf['Embarked'].map({'C': 0, 'S': 1, 'Q': 2})

def fillMissingAge(df):
	process_df = df[['Age', 'Pclass', 'Title', 'Sex', 'SibSp', 'Parch', 'FamilySize', 'FamilyLable']]
	known = process_df[process_df.Age.notnull()].iloc[:, :].values
	unknown = process_df[process_df.Age.isnull()].iloc[:, :].values
	X = known[:, 1:]
	y = known[:, 0]
	rfr = RandomForestRegressor(random_state = 0, n_estimators = 200, max_depth = 6, n_jobs = -1)
	rfr.fit(X,y)
	predicted = rfr.predict(unknown[:, 1:]).round(0)
	df.loc[df.Age.isnull(), 'Age'] = predicted
	return df

allDf = fillMissingAge(allDf)
allDf['AgeLable'] = allDf['Age'].apply(transAgeToLable)
allDf.to_csv("allData.csv")
print("Data processing ended successfully.", file = sys.stderr)
