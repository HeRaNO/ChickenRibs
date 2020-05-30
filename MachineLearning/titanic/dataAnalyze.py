'''
	dataAnalyze.py：用于分析数据。
	Author：HeRaNO
'''

import re
import numpy as np
import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

train = pd.read_csv('data\\train.csv')
test = pd.read_csv('data\\test.csv')

def printTrain():
	print(train.info())
	print(train.head())

def printTest():
	print(test.info())
	print(test.head())

def printTrainDescribe():
	print(train.describe())

def drawSexSurvived():
	print(train['Survived'].value_counts())
	Survived_0 = train.Sex[train.Survived == 0].value_counts()
	Survived_1 = train.Sex[train.Survived == 1].value_counts()
	df = pd.DataFrame({'Survived': Survived_1, 'Not Survived': Survived_0})
	df.plot(kind = 'bar', stacked = True)
	plt.xlabel("Sex")
	plt.ylabel("Count")
	plt.title("Sex - Survived")
	plt.show()

def drawPclassSurvived():
	Survived_0 = train.Pclass[train.Survived == 0].value_counts()
	Survived_1 = train.Pclass[train.Survived == 1].value_counts()
	df = pd.DataFrame({'Survived': Survived_1, 'Not Survived': Survived_0})
	df.plot(kind = 'bar', stacked = True)
	plt.xlabel("Pclass")
	plt.ylabel("Count")
	plt.title("Pclass - Survived")
	plt.show()

def drawEmbarkedSurvived():
	Survived_0 = train.Embarked[train.Survived == 0].value_counts()
	Survived_1 = train.Embarked[train.Survived == 1].value_counts()
	df = pd.DataFrame({'Survived': Survived_1, 'Not Survived': Survived_0})
	df.plot(kind = 'bar', stacked = True)
	plt.xlabel("Embarked")
	plt.ylabel("Count")
	plt.title("Embarked - Survived")
	plt.show()

def drawSibSpSurvived():
	Survived_0 = train.SibSp[train.Survived == 0].value_counts()
	Survived_1 = train.SibSp[train.Survived == 1].value_counts()
	df = pd.DataFrame({'Survived': Survived_1, 'Not Survived': Survived_0})
	df.plot(kind = 'bar', stacked = True)
	plt.xlabel("SibSp")
	plt.ylabel("Count")
	plt.title("SibSp - Survived")
	plt.show()

def drawParchSurvived():
	Survived_0 = train.Parch[train.Survived == 0].value_counts()
	Survived_1 = train.Parch[train.Survived == 1].value_counts()
	df = pd.DataFrame({'Survived': Survived_1, 'Not Survived': Survived_0})
	df.plot(kind = 'bar', stacked = True)
	plt.xlabel("Parch")
	plt.ylabel("Count")
	plt.title("Parch - Survived")
	plt.show()

def drawAgeSurvived():
	facet = sns.FacetGrid(train, hue = "Survived", aspect = 2)
	facet.map(sns.kdeplot, 'Age', shade = True)
	facet.set(xlim = (0, train['Age'].max()))
	facet.add_legend()
	plt.xlabel('Age')
	plt.ylabel('Density')
	plt.show()

def checkTicket(): # Bad attribute
	reg = re.compile(r'\s?(\d+)')
	x = set()
	notCat = set()
	cntNotCat = 0
	for i in train.Ticket:
		x.add(i)
	print(x)
	print(len(x) + cntNotCat)

def checkTrainName():
	print(set(train.Name.str.extract(r' ([A-Za-z]+)\.', expand=False)))

def checkTestName():
	print(set(test.Name.str.extract(r' ([A-Za-z]+)\.', expand=False)))

def drawTitleSurvived():
	train['Title'] = train.Name.str.extract(r' ([A-Za-z]+)\.', expand=False)
	Survived_0 = train.Title[train.Survived == 0].value_counts()
	Survived_1 = train.Title[train.Survived == 1].value_counts()
	df = pd.DataFrame({'Survived': Survived_1, 'Not Survived': Survived_0})
	df.plot(kind = 'bar', stacked = True)
	plt.xlabel("Title")
	plt.ylabel("Count")
	plt.title("Title - Survived")
	plt.show()

def drawTitleCatSurvived():
	train['Title'] = train.Name.str.extract(r' ([A-Za-z]+)\.', expand=False)
	Title_Dict = {}
	Title_Dict.update(dict.fromkeys(['Capt', 'Col', 'Major'], 'Officer'))
	Title_Dict.update(dict.fromkeys(['Jonkheer', 'Sir', 'Countess', 'Lady', 'Don'], 'Royalty'))
	Title_Dict.update(dict.fromkeys(['Dr', 'Rev'], 'Prof'))
	Title_Dict.update(dict.fromkeys(['Mme', 'Ms', 'Mrs'], 'Mrs'))
	Title_Dict.update(dict.fromkeys(['Mlle', 'Miss'], 'Miss'))
	Title_Dict.update(dict.fromkeys(['Mr'], 'Mr'))
	Title_Dict.update(dict.fromkeys(['Master'], 'Master'))
	train['Title'] = train['Title'].map(Title_Dict)
	sns.barplot(x = "Title", y = "Survived", data = train)
	plt.show()

def drawFamilySizeSurvived():
	train['FamilySize'] = train.SibSp + train.Parch + 1
	sns.barplot(x = "FamilySize", y = "Survived", data = train)
	plt.show()


