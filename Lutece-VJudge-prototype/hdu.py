import requests
import base64
from urllib import parse

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "http://acm.hdu.edu.cn/userloginex.php?action=login&cid=0&notice=0"

formData = {
	"username": username,
	"userpass": passwd,
	"login": "Sign In"
}

r = session.post(url, formData, allow_redirects=True)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)
# print(r.status_code)

url = "http://acm.hdu.edu.cn/submit.php?action=submit"

codeFile = open("2815.cpp", "r", encoding = "utf-8")
code = codeFile.read()

code = parse.quote(code)
codeb64 = base64.b64encode(code.encode()).decode()

formData = {
	'check': '0',
	'_usercode': codeb64,
	'problemid': "2815",
	'language': '0' # 0 for G++
}

r = session.post(url, formData)
# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)
