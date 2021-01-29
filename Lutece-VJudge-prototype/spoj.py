import requests

username = "" # Fill it
passwd = "" # Fill it

session = requests.Session()

url = "https://www.spoj.com/login"

formData = {
	'login_user': username,
	'password': passwd,
	'autologin': '1',
	'next_raw': '/'
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = "https://www.spoj.com/submit/complete/"

codeFile = open("TEST.cpp")
code = codeFile.read()

files = {'subm_file': None}

formData = {
	'file': code,
	'lang': '44', # 44 for C++14 (gcc 8.3)
	'problemcode': 'TEST',
	'submit': 'Submit!'
}

r = session.post(url, data = formData, files = files, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
