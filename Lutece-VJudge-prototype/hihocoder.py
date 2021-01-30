import requests

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "https://hihocoder.com/api/User/login.json"

formData = {
	"email": username,
	"passwd": passwd
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = "https://hihocoder.com/api/problem/submit.json"

codeFile = open("1000.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	'contest-id': '0',
	'problem-id': '1000',
	'source': code,
	'language': 'G++'
}

r = session.post(url, formData, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
