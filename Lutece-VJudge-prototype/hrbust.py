import requests
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_v1_5
import base64
import json

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

public_key = """-----BEGIN PUBLIC KEY-----
MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQC88fBRU1FaC5S537krMDVDapOZ
k44Nw+Yud69IPZYwk9HT0n6D7Pvp3mXp+Par6gp5HUW3tFs7/l3cTIqryEXMfJXR
F7FlneM64kLs/KZ2i0larVrz7QgcTb5oAuHeIE24Uc0ja+S83Hlc2Dk6z1TWkAjG
2f/p15xRfv/IO5yyywIDAQAB
-----END PUBLIC KEY-----
"""

formData = {
	"user_name": username,
	"password": passwd
}

msg = json.dumps(formData).replace(" ", "")

def rsa_encode(message, public_key):
	rsakey = RSA.importKey(public_key)
	cipher = PKCS1_v1_5.new(rsakey)
	cipher_text = base64.b64encode(
		cipher.encrypt(message.encode(encoding="utf-8")))
	return cipher_text.decode()

encrypt = rsa_encode(msg, public_key)

url = "http://acm.hrbust.edu.cn/index.php?m=User&a=login"

formData = {
	"encrypt": encrypt,
	"jumpUrl": ""
}

r = session.post(url, formData)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
print(r.status_code)

# TBC...
