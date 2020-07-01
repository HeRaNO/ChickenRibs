import sys
import json
import time
import random
import string
import hashlib

import requests

key = # Your Codeforces key
secret = # Your Codeforces secret
stdTime = # End time

def getRandomString():
	return ''.join(random.sample(string.ascii_letters + string.digits, 6))

def getSHA512(plain):
	hsh = hashlib.sha512()
	hsh.update(plain.encode('UTF-8'))
	return hsh.hexdigest()

def getNowTimeStr():
	return str(int(time.time()))

def getUserRating(userName):
	website = 'https://codeforces.com/api/user.rating'
	handle = 'handle=' + userName
	apiKey = 'apiKey=' + key
	pRand = getRandomString()
	time = 'time=' + getNowTimeStr()
	plain = pRand + '/user.rating?' + apiKey + '&' + handle + '&' + time + '#' + secret
	apiSig = 'apiSig=' + pRand + getSHA512(plain)
	website = website + '?' + handle + '&' + apiKey + '&' + time + '&' + apiSig
	r = requests.get(website)
	if r.status_code != 200 and r.status_code != 400:
		raise RuntimeError('Website returns status code: ' + str(r.status_code))
	return json.loads(r.text)

def getTop3Rating(rating):
	a = []
	for rec in rating:
		if int(rec['ratingUpdateTimeSeconds']) <= stdTime:
			a.append(rec['newRating'])
	if len(a) < 5:
		return 0
	a.sort(reverse = True)
	return a[2]

def makeRatingTable(userFile):
	file = open(userFile, 'r')
	for user in file.readlines():
		user = user.strip()
		userRating = getUserRating(user)
		if userRating['status'] == 'OK':
			stdRating = getTop3Rating(userRating['result'])
			print(user + ' ' + str(stdRating))
		else:
			print(user + ' ' + userRating['comment'])

if len(sys.argv) != 2:
	raise RuntimeError('Usage: ' + sys.argv[0] + ' <userFile>')

makeRatingTable(sys.argv[1])
