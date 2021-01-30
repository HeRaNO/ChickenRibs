import requests
from bs4 import BeautifulSoup
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA
import base64

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

baseUrl = "https://acm.ecnu.edu.cn"
url = baseUrl + '/login/'

r = session.get(url, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")

_csrf = soup.find("input", attrs = {"name": "csrfmiddlewaretoken"})["value"]
_next = soup.find("input", attrs = {"name": "next"})["value"]
_captcha_0 = soup.find("input", attrs = {"name": "captcha_0"})["value"]

public_key = soup.find("input", attrs = {"name": "public_key"})["value"]

imgUrl = soup.find("img", attrs = {"alt": "captcha"})["src"]
imgUrl = baseUrl + imgUrl

r = session.get(imgUrl, verify = False)

with open('ecnu.jpg', 'wb') as f:
	f.write(r.content)

_captcha_1 = input('input captcha: ')
_captcha_1 = _captcha_1.strip()

# Copy from https://github.com/F0RE1GNERS/eoj3/blob/master/utils/rsa_gen.py#L16
def rsa_encode(message, key):
	key = key.replace('-----BEGIN PUBLIC KEY-----', '')
	key = key.replace('-----END PUBLIC KEY-----', '')
	# Since it's coming from java/javascript, it's base 64 encoded.
	# Decode before importing.
	pubkey = RSA.importKey(base64.b64decode(key))
	cipher = PKCS1_OAEP.new(pubkey, hashAlgo=SHA256)
	encrypted = cipher.encrypt(bytes(message, encoding="utf-8"))
	return base64.b64encode(encrypted)

pwd = rsa_encode(passwd, public_key)

formData = {
	"csrfmiddlewaretoken": _csrf,
	"next": _next,
	"username": username,
	"password": pwd,
	"captcha_0": _captcha_0,
	"captcha_1": _captcha_1,
	"remember_me": "on",
	"public_key": public_key
}

r = session.post(url, formData, verify = False)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)
# print(r.status_code)

problemUrl = baseUrl + '/problem/1'
submitUrl = problemUrl + '/submit/'

r = session.get(problemUrl, verify = False)

soup = BeautifulSoup(r.text, features = "lxml")

_csrf = soup.find("input", attrs = {"name": "csrfmiddlewaretoken"})["value"]

codeFile = open("1000.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	"csrfmiddlewaretoken": _csrf,
	"problem": '1',
	"code": code,
	"lang": "cc17"
}

r = session.post(submitUrl, formData, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
print(r.status_code)
