import sys
import time
import pygame
import random
from pygame.locals import *

PIX = 80
SCRPIX = 60
SIZ = 0

class _2048Map(object):
	def __init__(self, siz):
		self.siz = siz
		self.scr = 0
		self.mp = [[0 for i in range(siz)] for i in range(siz)]
		self.add()
		self.add()

	def add(self):
		f = False
		for i in range(self.siz):
			for j in range(self.siz):
				if self.mp[i][j] == 0:
					f = True
					break
			if f:
				break
		if (not self.isOver()) and f:
			while True:
				pos = random.randint(0, self.siz * self.siz - 1)
				if self.mp[pos // self.siz][pos % self.siz] == 0:
					break
			x = random.randint(0, 3) and 2 or 4
			self.mp[pos // self.siz][pos % self.siz] = x

	def Leftize(self):
		isChanged = False
		for i in range(self.siz):
			left = []
			for j in range(self.siz):
				if self.mp[i][j]:
					left.append(self.mp[i][j])
			l = self.siz - len(left)
			for j in range(l):
				left.append(0)
			for j in range(self.siz):
				if left[i] != self.mp[i][j]:
					isChanged = True
					break

			pt = 0
			for j in range(1, self.siz):
				if left[j - 1] == left[j]:
					left[j - 1] <<= 1
					self.scr += left[j - 1]
					left[j] = 0
					if left[j - 1]:
						isChanged = True
			for j in left:
				if j:
					self.mp[i][pt] = j
					pt += 1
			for j in range(pt, self.siz):
				self.mp[i][j] = 0

		return isChanged

	def lturn(self):
		self.mp = [[self.mp[c][r] for c in range(self.siz)] for r in reversed(range(self.siz))]

	def isOver(self):
		for i in range(self.siz):
			for j in range(self.siz):
				if self.mp[i][j] == 0:
					return False
				if (j >= 1) and (self.mp[i][j] == self.mp[i][j - 1]):
					return False
				if (i >= 1) and (self.mp[i][j] == self.mp[i - 1][j]):
					return False
		return True

	def moveU(self):
		self.lturn()
		if self.Leftize():
			self.add()
		self.lturn()
		self.lturn()
		self.lturn()

	def moveD(self):
		self.lturn()
		self.lturn()
		self.lturn()
		if self.Leftize():
			self.add()
		self.lturn()

	def moveR(self):
		self.lturn()
		self.lturn()
		if self.Leftize():
			self.add()
		self.lturn()
		self.lturn()

	def moveL(self):
		if self.Leftize():
			self.add()

def showMap(mp):
	for i in range(mp.siz):
		for j in range(mp.siz):
			screen.blit(mp.mp[i][j] == 0 and block[(i + j) % 2] or block[2 + (i + j) % 2], (PIX * j, PIX * i))
			if mp.mp[i][j] != 0:
				mp_txt = mp_font.render(str(mp.mp[i][j]), True, (106, 90, 205))
				txt_rect = mp_txt.get_rect()
				txt_rect.center = (PIX * j + PIX / 2, PIX * i + PIX / 2)
				screen.blit(mp_txt, txt_rect)
	screen.blit(scr_block, (0, PIX * mp.siz))
	scr_txt = scr_font.render((mp.isOver() and "Game over with score " or "Score: ") + str(mp.scr), True, (106, 90, 205))
	txt_rect = scr_txt.get_rect()
	txt_rect.center = (PIX * SIZ / 2, PIX * SIZ + SCRPIX / 2)
	screen.blit(scr_txt, txt_rect)
	pygame.display.update()

pygame.init()
screen = pygame.display.set_mode((600,500))
pygame.display.set_caption("2048")
fnt = pygame.font.Font(None, 24)
txt = fnt.render("Press any key 4 to 9 for setting the size of map", True, (106, 90, 205))
screen.fill((245, 245, 245))
screen.blit(txt, (100, 100))
pygame.display.update()

while True:
	for event in pygame.event.get():
		if event.type == QUIT:
			sys.exit(0)
		elif event.type == pygame.KEYDOWN:
			if event.key == K_4 or event.key == K_KP4:
				SIZ = 4
				break
			elif event.key == K_5 or event.key == K_KP5:
				SIZ = 5
				break
			elif event.key == K_6 or event.key == K_KP6:
				SIZ = 6
				break
			elif event.key == K_7 or event.key == K_KP7:
				SIZ = 7
				break
			elif event.key == K_8 or event.key == K_KP8:
				SIZ = 8
				break
			elif event.key == K_9 or event.key == K_KP9:
				SIZ = 9
				break
	if SIZ:
		break

mp = _2048Map(SIZ)

screen = pygame.display.set_mode((PIX * SIZ, PIX * SIZ + SCRPIX))

block = [pygame.Surface((PIX, PIX)) for i in range(4)]
block[0].fill((152, 251, 152))
block[1].fill((240, 255, 255))
block[2].fill((0, 255, 127))
block[3].fill((225, 255, 255))

scr_block = pygame.Surface((PIX * SIZ, SCRPIX))
scr_block.fill((245, 245, 245))
mp_font = pygame.font.Font(None, PIX * 2 // 3)
scr_font = pygame.font.Font(None, SCRPIX // 2)

showMap(mp)

while not mp.isOver():
	for event in pygame.event.get():
		if event.type == QUIT:
			sys.exit(0)
		elif event.type == pygame.KEYDOWN:
			if event.key == K_w or event.key == K_UP:
				mp.moveU()
				break
			elif event.key == K_s or event.key == K_DOWN:
				mp.moveD()
				break
			elif event.key == K_a or event.key == K_LEFT:
				mp.moveL()
				break
			elif event.key == K_d or event.key == K_RIGHT:
				mp.moveR()
				break
	showMap(mp)

pygame.time.delay(3000)
