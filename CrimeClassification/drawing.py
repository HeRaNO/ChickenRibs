import matplotlib.pyplot as plt
import time as systime
import datetime as dt
import string
import seaborn as sns
import matplotlib.colors as colors


Trainset = pd.read_csv('train.csv', parse_dates = ['Dates'])


year = pd.get_dummies(Trainset.Dates.dt.year)
month = pd.get_dummies(Trainset.Dates.dt.month)
week = pd.get_dummies(Trainset.DayOfWeek)
hour = pd.get_dummies(Trainset.Dates.dt.hour)
district = pd.get_dummies(Trainset.PdDistrict)

plt.figure(figsize=(8,19))
year_group = train.groupby('year').size()
plt.subplot(311)
plt.plot(year_group.index[:-1],year_group[:-1],'ks-')
plt.xlabel('year')
month_group = train.groupby('month').size()
plt.subplot(312)
plt.plot(month_group,'ks-')
plt.xlabel('month')
day_group = train.groupby('day').size()
plt.subplot(313)
plt.plot(day_group,'ks-')
plt.xlabel('day')
plt.show()
