import requests
from bs4 import BeautifulSoup
import sys

username = "" # Fill it
passwd = "" # Fill it

session = requests.Session()

url = "https://www.codechef.com/login"

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")

_csrf = soup.find("input", attrs = {"name": "csrfToken"})["value"]

formData = {
	'name': username,
	'pass': passwd,
	'form_id': 'new_login_form',
	'op': 'Login',
	'csrfToken': _csrf
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = "https://www.codechef.com/submit/ACEBIT"

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")

formToken = soup.find("input", attrs = {"name": "form_token", "id": "edit-problem-submission-form-token"})["value"]

codeFile = open("ACEBIT.cpp")
code = codeFile.read()
nullFile = open("null")

files = {'files[sourcefile]': nullFile}

formData = {
	'language': '44', # 44 for C++14 (gcc 6.3.0)
	'problem_code': 'ACEBIT',
	'form_id': 'problem_submission',
	'form_token': formToken,
	"program": code
}

print(formData)

r = session.post(url, data = formData, files = files, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
