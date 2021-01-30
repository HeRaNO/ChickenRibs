import requests
from bs4 import BeautifulSoup

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "https://onlinejudge.org/"

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")

allHiddenTags = soup.findAll("input", attrs = {"type": "hidden"})

hiddenData = {}

for tag in allHiddenTags:
	hiddenData[tag["name"]] = tag["value"]

url = "https://onlinejudge.org/index.php?option=com_comprofiler&task=login"

formData = {
	'username': username,
	'passwd': passwd,
	'remember': 'yes',
	'Submit': 'Login'
}

formData.update(hiddenData)

r = session.post(url, formData, verify = False)

url = "https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=25&page=save_submission"

codeFile = open("100.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	'problemid': '',
	'category': '',
	'localid': '100',
	'language': '5', # 5 for C++ 11
	'code': code
}

files = {'codeupl': None}

r = session.post(url, data = formData, files = files, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
