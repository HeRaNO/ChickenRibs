import requests

session = requests.Session()

url = "http://acm.scu.edu.cn/soj/login.action"

username = "" # Fill it
passwd = "" # Fill it

formData = {
	'back': '2',
	'id': username,
	'password': passwd,
	'submit': 'login'
}

r = session.post(url, formData)

# page = open("out.html", "w", encoding = "utf-8")
# page.write()

url = "http://acm.scu.edu.cn/soj/validation_code"

r = session.get(url)

with open('scu.jpg', 'wb') as f:
	f.write(r.content)

captcha = input('input captcha: ')
captcha = captcha.strip()

codeFile = open("1000.cpp", "r", encoding = "gbk")
code = codeFile.read()

url = "http://acm.scu.edu.cn/soj/submit.action"

formData = {
	"problemId": "1001",
	"validation": captcha,
	"language": "C++",
	"source": code,
	"submit": "Submit"
}

r = session.post(url, data = formData)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
