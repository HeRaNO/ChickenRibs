import sys
import json
import time

import requests

def getUserRating(userName):
	website = 'https://codeforces.com/api/user.rating?handle=' + userName
	r = requests.get(website)
	if r.status_code != 200 and r.status_code != 400:
		raise RuntimeError('Website returns status code: ' + str(r.status_code))
	return json.loads(r.text)

def getTop3Rating(rating):
	allRating = []
	for rec in rating:
		allRating.append(rec['newRating'])
	if len(allRating) < 5:
		return '0'
	allRating.sort(reverse = True)
	return str(allRating[2])

def makeRatingTable(userFile):
	file = open(userFile, 'r')
	for user in file.readlines():
		user = user.strip()
		userRating = getUserRating(user)
		if userRating['status'] == 'OK':
			print(user + ' ' + getTop3Rating(userRating['result']))
		else:
			print(user + ' ' + userRating['comment'])

if len(sys.argv) != 2:
	raise RuntimeError('Usage: ' + sys.argv[0] + ' <userFile>')

makeRatingTable(sys.argv[1])
