'''
	titanic.py：预测泰坦尼克号乘客是否生还。
	Author：HeRaNO
'''

import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from sklearn import svm, metrics
from sklearn.model_selection import GridSearchCV, train_test_split, RepeatedKFold, cross_val_score
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression, LogisticRegressionCV

allDf = pd.read_csv('allData.csv', index_col = 0)
train = allDf[allDf.Survived.notnull()].iloc[:, :].values
test = allDf[allDf.Survived.isnull()].iloc[:, :].values

X = train[:, 1:]
y = train[:, 0]
testX = test[:, 1:]
print(testX)

def testRandomForest(X, y):
	param_test = {'n_estimators': list(range(20, 40, 1)), 'max_depth': list(range(3, 10, 1))}
	model = RandomForestClassifier(random_state = 10, max_features = 'sqrt')
	gsearch = GridSearchCV(model, param_test, n_jobs = -1, verbose = 1)
	gsearch.fit(X, y)
	best_parameters = gsearch.best_estimator_.get_params()
	print(best_parameters)

def runRandomForest(X, y):
	model = RandomForestClassifier(n_estimators = 24, max_depth = 5, max_features = 'sqrt')
	model.fit(X, y)

def getScore(X, y):
	model = RandomForestClassifier(n_estimators = 22, max_depth = 4, warm_start = True)
	cv_score = cross_val_score(model, X, y, cv = 10)
	avg = np.mean(cv_score)
	std = np.std(cv_score)
	print("CV Score : Mean - %.7g | Std - %.7g " % (avg, std))
	print("[%.7g, %.7g]" % (avg - 2 * std, avg + 2 * std))

def testLogisticRegression(X, y):
	model = LogisticRegression(C = 10, penalty = 'l2', solver = 'lbfgs', n_jobs = -1, max_iter = 10000)
	model.fit(X, y)
	cv_score = cross_val_score(model, X, y, cv = 10)
	print("CV Score : Mean - %.7g | Std - %.7g " % (np.mean(cv_score), np.std(cv_score)))

def testSVM(X, y):
	param_test = {'C': [1e-3, 1e-2, 1e-1, 1, 10, 100, 1000], 'gamma': [0.005, 0.003, 0.001, 0.0001]}
	model = svm.SVC(kernel = 'rbf', decision_function_shape = 'ovr', probability = True)
	gsearch = GridSearchCV(model, param_test, n_jobs = -1, verbose = 1)
	gsearch.fit(X, y)
	best_parameters = gsearch.best_estimator_.get_params()
	print(best_parameters)

def runSVM(X, y):
	model = svm.SVC(kernel = 'rbf', decision_function_shape = 'ovr', probability = True, C = 100, gamma = 0.005)
	cv_score = cross_val_score(model, X, y, cv = 10)
	avg = np.mean(cv_score)
	std = np.std(cv_score)
	print("CV Score : Mean - %.7g | Std - %.7g " % (avg, std))
	print("[%.7g, %.7g]" % (avg - 2 * std, avg + 2 * std))

def predict(X, y, testX):
	model = RandomForestClassifier(n_estimators = 22, max_depth = 4, warm_start = True)
	cv_score = cross_val_score(model, X, y, cv = 10)
	avg = np.mean(cv_score)
	std = np.std(cv_score)
	print("CV Score : Mean - %.7g | Std - %.7g " % (avg, std))
	print("[%.7g, %.7g]" % (avg - 2 * std, avg + 2 * std))
	model.fit(X, y)
	return model.predict(testX)

sub = predict(X, y, testX)
sdf = pd.DataFrame({"Survived": sub.astype(np.int32)})
sdf.to_csv("submission.csv")
