import numpy as np
import matplotlib.image as io
import matplotlib.pyplot as plt

alpha = 30
seedX = 998244353
seedY = 1000000007

''' First alpha = 5
oriFile = "qrcode.png"
waterMarkFile = "testwm.png"
outFile = "watermarked.png"
'''

''' Second alpha = 30
oriFile = "test.png"
waterMarkFile = "website.png"
outFile = "test_wmed.png"
'''

ori = io.imread(oriFile)
waterMark = io.imread(waterMarkFile)
ori = ori[:, :, :3]
waterMark = waterMark[:, :, :3]
oriN, oriM, oriA = ori.shape
watermarkN, watermarkM, watermarkR = waterMark.shape

# Randomlize
TH = np.zeros((oriN // 2, oriM, oriA))
TH1 = np.zeros((oriN // 2, oriM, oriA))
TH1[0 : watermarkN, 0 : watermarkM, :] = waterMark.copy()
THN, THM, THR = TH.shape

plt.imshow(TH1)
plt.show()

randX = np.arange(THN)
np.random.seed(seedX)
randX = np.random.permutation(randX)

randY = np.arange(THM)
np.random.seed(seedY)
randY = np.random.permutation(randY)

for i in range(0, THN):
	for j in range(0, THM):
		for k in range(0, THR):
			TH[i][j][k] = TH1[randX[i]][randY[j]][k].copy()

plt.imshow(TH)
plt.show()

# Make symmetric

_waterMark = np.zeros((oriN, oriM, oriA))
_waterMark[0 : THN, 0 : THM, :] = TH.copy()

for i in range(0, THN):
	for j in range(0, THM):
		for k in range(0, THR):
			_waterMark[oriN - i - 1][oriM - j - 1][k] = TH[i][j][k].copy()

plt.imshow(_waterMark)
plt.show()

# Do FFT

oriR = np.fft.fft2(ori[:, :, 0])
oriG = np.fft.fft2(ori[:, :, 1])
oriB = np.fft.fft2(ori[:, :, 2])

_waterMarkedR = oriR + alpha * _waterMark[:, :, 0]
_waterMarkedG = oriG + alpha * _waterMark[:, :, 1]
_waterMarkedB = oriB + alpha * _waterMark[:, :, 2]

waterMarkedR = np.fft.ifft2(_waterMarkedR)
waterMarkedG = np.fft.ifft2(_waterMarkedG)
waterMarkedB = np.fft.ifft2(_waterMarkedB)

waterMarked = np.zeros((oriN, oriM, oriA + 1))

waterMarked[:, :, 0] = np.real(waterMarkedR).copy()
waterMarked[:, :, 1] = np.real(waterMarkedG).copy()
waterMarked[:, :, 2] = np.real(waterMarkedB).copy()
waterMarked[:, :, 3] = np.ones((oriN, oriM))

waterMarked = np.clip(waterMarked, 0, 1)

plt.imshow(waterMarked)
plt.show()
io.imsave(outFile, waterMarked)

# Decode instantly

_waterMarkedR = np.fft.fft2(waterMarkedR)
_waterMarkedG = np.fft.fft2(waterMarkedG)
_waterMarkedB = np.fft.fft2(waterMarkedB)

oriR = np.fft.fft2(ori[:, :, 0])
oriG = np.fft.fft2(ori[:, :, 1])
oriB = np.fft.fft2(ori[:, :, 2])

_waterMark = np.zeros((oriN, oriM, oriA))

_waterMark[:, :, 0] = (_waterMarkedR - oriR) / alpha
_waterMark[:, :, 1] = (_waterMarkedG - oriG) / alpha
_waterMark[:, :, 2] = (_waterMarkedB - oriB) / alpha

_waterMark = np.real(_waterMark)
waterMarkOut = np.zeros((oriN, oriM, oriA))

for i in range(0, THN):
	for j in range(0, THM):
		for k in range(0, THR):
			waterMarkOut[randX[i], randY[j], k] = _waterMark[i, j, k]

for i in range(0, THN):
	for j in range(0, THM):
		waterMarkOut[oriN - i - 1, oriM - j - 1, :] = waterMarkOut[i, j, :].copy()

plt.imshow(waterMarkOut)
plt.show()
