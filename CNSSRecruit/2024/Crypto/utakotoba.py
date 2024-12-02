from data import *
from Crypto.Util.strxor import strxor
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad

png_first_blk = b'\x89\x50\x4e\x47\x0d\x0a\x1a\x0a\x00\x00\x00\x0d\x49\x48\x44\x52'

iv = strxor(enc_pic[:16], png_first_blk)

cipher = AES.new(key = key, mode = AES.MODE_OFB, iv = iv)
with open("flag.png", "wb") as f:
	f.write(png_first_blk + unpad(cipher.decrypt(enc_pic[16:]), 16))
