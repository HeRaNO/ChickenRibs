import requests
from bs4 import BeautifulSoup

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "https://www.e-olymp.com/en/login-check"

formData = {
	"_username": username,
	"_password": passwd,
	'_remember_me': "on"
}

r = session.post(url, formData, verify = False)

url = "https://www.e-olymp.com/en/submissions/submit"

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")

submit_token = soup.find("input", attrs = {"name": "submit[_token]"})["value"]

codeFile = open("1.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	"submit[problem]": "1",
	"submit[compiler]": "gpp",
	"submit[source]": code,
	"submit[_token]": submit_token
}

r = session.post(url, formData, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
