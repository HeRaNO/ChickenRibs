import requests
import hmac
import sys
import re

session = requests.Session()

url = "https://uoj.ac/login"

username = "" # Fill it
passwd = "" # Fill it

r = session.get(url, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)
# print(r.status_code)

_token = re.findall(r"_token : \"(.*)\"", r.text)[0]

salt = "uoj233_wahaha!!!!"

pwd = hmac.new(bytes(salt, encoding = "utf-8"), bytes(passwd, encoding = "utf-8"), digestmod = 'MD5').hexdigest()

formData = {
	"_token": _token,
	"login": "",
	"username": username,
	"password": pwd
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)
# print(r.status_code)

url = "https://uoj.ac/problem/1"

codeFile = open("1000.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	"_token": _token,
	"answer_answer_language": "C++",
	"answer_answer_upload_type": "editor",
	"answer_answer_editor": code,
	"submit-answer": 'answer'
}

file = {"answer_answer_file": None}

r = session.post(url, formData, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
print(r.status_code)
