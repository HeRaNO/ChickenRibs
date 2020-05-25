'''
	datackeck.py：用于检查 MNIST 数据。
	Author：HeRaNO
'''

import gzip
import pickle
import numpy as np
import collections

f = gzip.open('mnist.pkl.gz', 'rb')   
training_data, vali_data, test_data = pickle.load(f, encoding = 'bytes')
f.close()

y = training_data[1]
print(y)
print(collections.Counter(y))
