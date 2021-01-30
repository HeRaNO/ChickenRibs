import requests
import json
import base64
import sys

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "http://acm.hit.edu.cn/api/v1/user/getCaptcha/"

r = session.get(url, verify = False)
captcha = json.loads(r.text)

token = captcha["token"]
imgB64 = captcha["captcha"]

imgdata = base64.b64decode(bytes(imgB64, encoding = "utf-8"))
captchaImg = open('hit.jpg','wb')
captchaImg.write(imgdata)
captchaImg.close()

captcha = input('input captcha: ')
captcha = captcha.strip()

url = "http://acm.hit.edu.cn/api/v1/user/login/"

formData = {
	"captcha": captcha,
	"password": passwd,
	"token": token,
	"username": username
}

r = session.post(url, json = formData, verify = False)

token = json.loads(r.text)["token"]

url = "http://acm.hit.edu.cn/api/v1/judge/submit/"

codeFile = open("1002.cpp", "r", encoding = "utf-8")
code = codeFile.read()

codeb64 = base64.b64encode(code.encode()).decode()

formData = {
	"code": codeb64,
	"language": "G++",
	"pid": "1002",
	"public": "false" # Errrrr......
}

hdr = {
	"Authorization": "JWT " + token
}

r = session.post(url, json = formData, headers = hdr, verify = False)

print(r.text)
print(r.status_code)
