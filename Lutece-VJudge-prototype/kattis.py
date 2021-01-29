import requests
from bs4 import BeautifulSoup
import sys

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "https://open.kattis.com/login/email"

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")
_csrf = soup.find("input", attrs = {"name": "csrf_token"})["value"]

formData = {
	'csrf_token': _csrf,
	'user': username,
	'password': passwd,
	'submit': 'Submit'
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = 'https://open.kattis.com/problems/hello/submit'

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")
_csrf = soup.find("input", attrs = {"name": "csrf_token"})["value"]
_submit_ctr = soup.find("input", attrs = {"name": "submit_ctr"})["value"]

codeFile = open("hello.cpp")
code = codeFile.read()
files = {'sub_file[]': None}

formData = {
	'csrf_token': _csrf,
	'type': 'editor',
	'sub_code': code,
	'problem': 'hello',
	'language': 'C++',
	'submit': 'Submit',
	'submit_ctr': _submit_ctr
}

r = session.post(url, data = formData, files = files, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
