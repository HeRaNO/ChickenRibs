import requests
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_v1_5
import base64

session = requests.Session()

public_key = """-----BEGIN PUBLIC KEY-----
MIGeMA0GCSqGSIb3DQEBAQUAA4GMADCBiAKBgGTNlnTkCV1UvqhwEwoTBSgve1Ic
eORoDpB8lV7g358xqoXTHFj7i+4SP3mD48VmGFUyKu+ZiH8hN0Od6s6+bttQ7YbE
vSRwEjwfVC9DCCPukAHtirBSCDUqbFJPg8BfsHIOtPDx0CJCNmzutNkSnhD/lNad
JvHU/Gl9NitAceZlAgMBAAE=
-----END PUBLIC KEY-----
"""

url = "https://www.51nod.com/UserWriter/Login"

username = "" # Fill it
passwd = "" # Fill it

def rsa_encode(message, public_key):
	rsakey = RSA.importKey(public_key)
	cipher = PKCS1_v1_5.new(rsakey)
	cipher_text = base64.b64encode(
		cipher.encrypt(message.encode(encoding="utf-8")))
	return cipher_text.decode()

pwd = rsa_encode(passwd, public_key)

formData = {
	'Username': username,
	'Password': pwd,
	'IsPersistent': "true"
}

r = session.post(url, formData, verify = False)

# print(r.status_code)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = "https://www.51nod.com/JudgeWriter/Append"

codeFile = open("1000.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	"ProblemId": "1000",
	"Language": "12", # 12 for C++ 11
	"IsPublic": "true",
	"ProgramContent": code
}

r = session.post(url, formData, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
