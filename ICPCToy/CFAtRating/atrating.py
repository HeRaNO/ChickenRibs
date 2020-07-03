import sys

import requests
from bs4 import BeautifulSoup

def getUserRating(userName):
	website = 'https://atcoder.jp/users/' + userName + '/history'
	r = requests.get(website)

	if r.status_code != 200 and r.status_code != 404:
		raise RuntimeError('Website returns status code: ' + str(r.status_code))

	if r.status_code == 404:
		return 'not found'

	soup = BeautifulSoup(r.text, 'lxml')
	allRating = []
	for idx, tr in enumerate(soup.find_all('tr')):
		if idx != 0:
			tds = tr.find_all('td')
			rating = tds[4].contents[0]
			if rating == '-':
				continue
			rating = rating.contents[0]
			allRating.append(int(rating))
	if len(allRating) < 5:
		return 0
	allRating.sort(reverse = True)
	return allRating[2]

def makeRatingTable(userFile):
	file = open(userFile, 'r')
	for user in file.readlines():
		user = user.strip()
		print(user + ' ' + str(getUserRating(user)))

if len(sys.argv) != 2:
	raise RuntimeError('Usage: ' + sys.argv[0] + ' <userFile>')

makeRatingTable(sys.argv[1])
