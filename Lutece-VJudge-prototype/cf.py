import requests
from bs4 import BeautifulSoup
import sys

username = "" # Fill it
passwd = "" # Fill it

def calcTta(_39ce7):
	n = len(_39ce7)
	c = 0
	_tta = 0
	while c < n:
		_tta = (_tta + (c + 1) * (c + 2) * ord(_39ce7[c])) % 1009
		if c % 3 == 0:
			_tta += 1
		if c % 2 == 0:
			_tta *= 2
		if c > 0:
			_tta -= ((ord(_39ce7[c // 2]) // 2)) * (_tta % 5)
		while _tta < 0:
			_tta += 1009
		while _tta >= 1009:
			_tta -= 1009
		c += 1
	return str(_tta)

session = requests.Session()

url = 'https://codeforces.com/enter'

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features="lxml")

_csrf = soup.find(attrs = {"name": "X-Csrf-Token"})['content']

_39ce7 = requests.utils.dict_from_cookiejar(r.cookies)["39ce7"]

_tta = calcTta(_39ce7)

formData = {
	'csrf_token': _csrf,
	'_tta': _tta,
	'action': 'enter',
	'handleOrEmail': username,
	'password': passwd,
	'remember': 'on'
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = 'https://codeforces.com/problemset/submit'

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features="lxml")

_csrf = soup.find(attrs = {"name": "X-Csrf-Token"})['content']

# print(r.cookies)

# _39ce7 = requests.utils.dict_from_cookiejar(r.cookies)["39ce7"]

# _tta = calcTta(_39ce7)

codeFile = open("1475B.cpp", "r")
code = codeFile.read()

formData = {
	'csrf_token': _csrf,
	'_tta': _tta,
	'action': 'submitSolutionFormSubmitted',
	"submittedProblemCode": "1475B",
	"programTypeId": "54", # 54 for GNU G++17 7.3.0
	"source": code,
	"sourceFile": "",
	"sourceCodeConfirmed": "true",
	"doNotShowWarningAgain": "on"
}

url += '?csrf_token=' + _csrf

r = session.post(url, formData, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
# The first record is the submission
