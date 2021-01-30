import requests
import hashlib
from bs4 import BeautifulSoup

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "https://passport.jisuanke.com/"

r = session.get(url, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

cookies = requests.utils.dict_from_cookiejar(r.cookies)

_csrf = cookies["XSRF-TOKEN"]

hdr = {
	'x-xsrf-token': _csrf,
	'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36'
}

passwd = hashlib.md5(bytes(passwd, encoding = "utf-8")).hexdigest()

formData = {
	'account': username,
	'pwd': passwd,
	'save': '1'
}

url = "https://passport.jisuanke.com/auth/login"

r = session.post(url, data = formData, headers = hdr, cookies = cookies, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = "https://nanti.jisuanke.com/t/T1001"

r = session.get(url, verify = False)

cookies = requests.utils.dict_from_cookiejar(r.cookies)

_csrf = cookies["XSRF-TOKEN"]

hdr = {
	'x-xsrf-token': _csrf,
	'user-agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/88.0.4324.104 Safari/537.36'
}

url = "https://nanti.jisuanke.com/solve/submit"

codeFile = open("T1004.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	'id': '34513',
	'language': 'c++14',
	'file[]': 'main.cpp',
	'codes[]': code
}

r = session.post(url, data = formData, headers = hdr, cookies = cookies, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
