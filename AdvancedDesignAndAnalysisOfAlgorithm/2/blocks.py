from math import sqrt

class Q_2(object): # Let's make it Q(sqrt(2)) a.k.a. a + b sqrt(2)
	def __init__(self, a, b):
		self.a = a
		self.b = b
	def __lt__(self, other): # Get rid of floating number
		a, b = self.a, self.b
		c, d = other.a, other.b
		if (a - c) * (d - b) <= 0:
			return a - c < d - b
		sgn = 1 if a > c else -1
		return sgn * (a - c) ** 2 < sgn * 2 * (d - b) ** 2
	def __add__(self, other):
		a, b = self.a, self.b
		c, d = other.a, other.b
		return Q_2(a + c, b + d)
	def __str__(self):
		return ("{} + {}sqrt(2)".format(self.a, self.b))

class AreaBlock(object):
	def __init__(self, fr, kind=0, g=Q_2(0, 0), x=0, y=0):
		self.fr = fr
		self.kind = kind
		self.x = x
		self.y = y
		self.g = g
		self.f = Q_2(0, 0) 

	def get_coordinate(self):
		return (self.x, self.y)

	def __lt__(self, other):
		return self.f < other.f
