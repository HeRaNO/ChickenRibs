import numpy as np
import pandas as pd
from operator import itemgetter, attrgetter  

from sklearn.metrics import log_loss
from sklearn.preprocessing import LabelEncoder
from sklearn.model_selection import train_test_split

from sklearn.svm import SVC
from sklearn.naive_bayes import BernoulliNB
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression

# Read the data
Trainset = pd.read_csv('train.csv', parse_dates = ['Dates'])
Testset = pd.read_csv('test.csv', parse_dates = ['Dates'])
siz = len(Testset)

# Prework...
label = LabelEncoder()
crime = label.fit_transform(Trainset.Category)

year = pd.get_dummies(Trainset.Dates.dt.year)
month = pd.get_dummies(Trainset.Dates.dt.month)
week = pd.get_dummies(Trainset.DayOfWeek)
hour = pd.get_dummies(Trainset.Dates.dt.hour)
district = pd.get_dummies(Trainset.PdDistrict)

Dataset = pd.concat([year, month, week, hour, district], axis = 1)

'''
Dataset['crime'] = crime
train, valid = train_test_split(Dataset, train_size=0.8)

train_y = train['crime']
train.drop(['crime'], axis=1, inplace = True)

valid_y = valid['crime']
valid.drop(['crime'], axis=1, inplace = True)
'''
# Also prework...
year = pd.get_dummies(Testset.Dates.dt.year)
month = pd.get_dummies(Testset.Dates.dt.month)
week = pd.get_dummies(Testset.DayOfWeek)
hour = pd.get_dummies(Testset.Dates.dt.hour)
district = pd.get_dummies(Testset.PdDistrict)

Test = pd.concat([year, month, week, hour, district], axis = 1)

# Prework finished!

def Run(model):
	model.fit(train, train_y)
	predict = model.predict(valid)
	error_index = np.nonzero(valid_y - predict)[0]
	print ("Accuracy: %.10f"%(len(error_index) / len(valid)))

# Now study...
'''
1. LogisticRegression
Accuracy:
0.15  77.21666667%
0.1   77.16500000%
0.075 77.23583333%
0.07  77.05583333%
0.01  77.09166667%

model = LogisticRegression(C = 0.15)
Run(model)

'''
model = LogisticRegression(C = 0.075)
# Run(model)
'''
2. RandomForestClassifier
Accuracy:
30 11 77.56833333%
30 13 77.28916667%
30 15 76.95166667%
30 20 76.96500000%
35 20 77.10916667%
40 11 77.41166667%
40 13 77.35583333%
45 11 77.16166667%
Sometimes Memory Error!!!

model = RandomForestClassifier(n_estimators = 35, max_depth = 20)
Run(model)
model.fit(train, train_y)
predict = np.array(model.predict_proba(valid))
print ("Accuracy: %f"%(log_loss(valid_y, predict)))
'''

'''
3. BernoulliNB
Accuracy: 77.11583333%

model = BernoulliNB()
model.fit(train, train_y)
predict = np.array(model.predict_proba(valid))
print ("Accuracy: %f"%(log_loss(valid_y, predict)))
'''

'''
4. SVC
Accuracy: NaN

TLE!

model = SVC()
Run(model)
'''

'''
5. KNeighborsClassifier
Accuracy: NaN

TLE!

model = KNeighborsClassifier(n_neighbors=3)
Run(model)
'''

# Output answer
model.fit(Dataset, crime)
test_pre = np.array(model.predict_proba(Test))

col_names = np.sort(Trainset['Category'].unique())
result = pd.DataFrame(data = test_pre, columns = col_names)

n = len(col_names)
out = []

for i in range(0, siz):
	x = {}
	for j in range(0, n):
		x[col_names[j]] = result.iloc[i, j]
	q = sorted(x.items(), key=itemgetter(1), reverse=True)
	t = []
	for j in range(0, 5):
		t.append(q[j][0])
	out.append(t)

result = pd.DataFrame(data = out)

result.to_csv('test_output.csv', index=False)

print ('Finished!')
