import requests
import base64

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "http://poj.openjudge.cn/api/auth/login/"

formData = {
	"redirectUrl": "",
	"email": username,
	"password": passwd
}

r = session.post(url, formData)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = "http://poj.openjudge.cn/api/solution/submit/"

codeFile = open("C17A.cpp", "r", encoding = "utf-8")
code = codeFile.read()

codeb64 = base64.b64encode(code.encode()).decode()

formData = {
	"contestId": "2",
	"problemNumber": "C17A",
	"sourceEncode": "base64",
	"language": "G++",
	"source": codeb64,
}

r = session.post(url, formData)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)

