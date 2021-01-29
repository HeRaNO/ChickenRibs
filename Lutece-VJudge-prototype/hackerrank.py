import requests
from bs4 import BeautifulSoup
import sys

username = "" # Fill it
passwd = "" # Fill it

session = requests.Session()

url = "https://www.hackerrank.com/auth/login"

user_agent = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36'

uhdr = {
	'user-agent': user_agent
}

r = session.get(url, headers = uhdr, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")

_csrf = soup.find("meta", attrs = {"name": "csrf-token"})["content"]

formData = {
	'fallback': "true",
	'login': username,
	'password': passwd,
	'remember_me': "true"
}

hdr = {
	'x-csrf-token': _csrf,
	'user-agent': user_agent
}

url = "https://www.hackerrank.com/rest/auth/login"

r = session.post(url, json = formData, headers = hdr, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = "https://www.hackerrank.com/challenges/compare-the-triplets/problem"

r = session.get(url, headers = uhdr, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")

_csrf = soup.find("meta", attrs = {"name": "csrf-token"})["content"]

url = "https://www.hackerrank.com/rest/contests/master/challenges/compare-the-triplets/submissions"

codeFile = open("compare-the-triplets.cpp")
code = codeFile.read()

formData = {
	"code": code,
	"contest_slug": "master",
	"language": "cpp14",
	"playlist_slug": ""
}

hdr = {
	'x-csrf-token': _csrf,
	'user-agent': user_agent
}

r = session.post(url, json = formData, headers = hdr, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
