import requests

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "http://acm.fzu.edu.cn/login.php?act=1&dir="

formData = {
	"uname": username,
	"upassword": passwd,
	"submit": "Submit"
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "iso8859-1")
# page.write(r.text)

url = "http://acm.fzu.edu.cn/submit.php?act=5"

codeFile = open("1000.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	"usr": username,
	"lang": '0', # 0 for GNU C++
	"pid": '1000',
	"code": code,
	"submit": 'Submit'
}

r = session.post(url, formData, verify = False)

page = open("out.html", "w", encoding = "iso8859-1")
page.write(r.text)
