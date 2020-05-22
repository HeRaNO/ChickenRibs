import numpy as np
import matplotlib.image as io
import matplotlib.pyplot as plt

alpha = 30
seedX = 998244353
seedY = 1000000007

''' First alpha = 5
oriFile = "qrcode.png"
waterMarkedFile = "watermarked.png"
outFile = "ex_testwm.png"
'''

''' Second alpha = 30
oriFile = "test.png"
waterMarkedFile = "test_wmed.png"
outFile = "ex_website.png"
'''

ori = io.imread(oriFile)
waterMarked = io.imread(waterMarkedFile)
ori = ori[:, :, :3]
waterMarked = waterMarked[:, :, :3]
oriN, oriM, oriA = ori.shape

_waterMarkedR = np.fft.fft2(waterMarked[:, :, 0])
_waterMarkedG = np.fft.fft2(waterMarked[:, :, 1])
_waterMarkedB = np.fft.fft2(waterMarked[:, :, 2])

oriR = np.fft.fft2(ori[:, :, 0])
oriG = np.fft.fft2(ori[:, :, 1])
oriB = np.fft.fft2(ori[:, :, 2])

_waterMark = np.zeros((oriN, oriM, oriA))

_waterMark[:, :, 0] = (_waterMarkedR - oriR) / alpha
_waterMark[:, :, 1] = (_waterMarkedG - oriG) / alpha
_waterMark[:, :, 2] = (_waterMarkedB - oriB) / alpha

THN = oriN // 2
THM = oriM
THR = oriA

randX = np.arange(THN)
np.random.seed(seedX)
randX = np.random.permutation(randX)

randY = np.arange(THM)
np.random.seed(seedY)
randY = np.random.permutation(randY)

waterMarkOut = np.zeros((oriN, oriM, oriA))

for i in range(0, THN):
	for j in range(0, THM):
		for k in range(0, THR):
			waterMarkOut[randX[i], randY[j], k] = _waterMark[i, j, k].copy()

for i in range(0, THN):
	for j in range(0, THM):
		waterMarkOut[oriN - i - 1, oriM - j - 1, :] = waterMarkOut[i, j, :].copy()

_waterMarkOut = np.real(waterMarkOut).copy()
_waterMarkOut = np.clip(_waterMarkOut, 0, 1)

plt.imshow(_waterMarkOut)
plt.show()
io.imsave(outFile, _waterMarkOut)
