import time
import random
from Crypto.Util.number import *
from mt19937predictor import MT19937Predictor

rnd = random.Random()

for l in range(10000):
	stream1 = random.Random(rnd.getrandbits(32))
	stream2 = random.Random(rnd.getrandbits(32))

	predictor = MT19937Predictor()

	for _ in range(624):
		a = stream1.getrandbits(32)
		b = stream2.getrandbits(32)
		predictor.setrandbits(a ^ b, 32)

	a = stream1.getrandbits(32)
	b = stream2.getrandbits(32)

	c = predictor.getrandbits(32)

	assert a ^ b == c
