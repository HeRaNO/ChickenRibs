'''
	hnr.py：用于手写数字识别，采用 SVM 方法。
	Author：HeRaNO
'''

import gzip
import pickle
import numpy as np
from sklearn import svm
import matplotlib.pyplot as plt
from sklearn.model_selection import GridSearchCV

f = gzip.open('mnist.pkl.gz', 'rb')   
training_data, vali_data, test_data = pickle.load(f, encoding = 'bytes')
f.close()

X = training_data[0][:6000]
y = training_data[1][:6000]

'''
	因为家里电脑不太行，实在跑得太慢，所以缩减了数据集
'''

# model = svm.SVC(kernel = 'rbf', decision_function_shape = 'ovr', probability = True)
# param_grid = {'C': [1e-3, 1e-2, 1e-1, 1, 10, 100, 1000], 'gamma': [0.005, 0.003, 0.001, 0.0001]}
# grid_search = GridSearchCV(model, param_grid, n_jobs = -1, verbose = 1)
# grid_search.fit(X, y)
# best_parameters = grid_search.best_estimator_.get_params()
model = svm.SVC(kernel = 'rbf', C = 100, gamma = 0.03, decision_function_shape = 'ovr', probability = True)
model.fit(X,y)

X_test = test_data[0]
y_test = test_data[1]
predictions = [int(a) for a in model.predict(X_test)]
num_correct = sum(int(a == y) for a, y in zip(predictions, y_test))
print ("%s of %s test values correct." % (num_correct, len(y_test)))

# 9622 / 10000 ???
