import requests
from bs4 import BeautifulSoup
import sys

username = "" # Fill it
passwd = "" # Fill it

session = requests.Session()

url = 'https://atcoder.jp/login'

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features="lxml")
_csrf = soup.find("input", attrs={"name": "csrf_token"})["value"]

formData = {
	'csrf_token': _csrf,
	'username': username,
	'password': passwd
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = 'https://atcoder.jp/contests/abc189/submit'

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features="lxml")
_csrf = soup.find("input", attrs={"name": "csrf_token"})["value"]

codeFile = open("189A.cpp", "r")
code = codeFile.read()

formData = {
	'csrf_token': _csrf,
	'data.TaskScreenName': 'abc189_a',
	'data.LanguageId': "4003", # 4003 for C++ (GCC 9.2.1)
	'sourceCode': code,
	"input-open-file": ""
}

r = session.post(url, formData, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
