from PIL import Image
from numpy import asarray, uint8

GRAY = (127, 127, 127, 255)
BLUE = (75, 174, 234, 255)
YELLOW = (246, 193, 67, 255)
WHITE = (255, 255, 255, 255)
RED = (255, 0, 0, 255)
GREEN = (0, 255, 0, 255)
BORDER = (0, 0, 0, 255)
SQUARE_SIZE = 20
LINE_WIDTH = 1

def convert_array_to_pixel(arr, path, path_oppo):
	n, m = len(arr), len(arr[0])
	pixels = []
	for row in arr:
		line = []
		for c in row:
			if c == 'g':
				line.append(GRAY)
			elif c == 'b':
				line.append(BLUE)
			elif c == 'y':
				line.append(YELLOW)
			elif c == 'w':
				line.append(WHITE)
			else:
				raise RuntimeError('Invalid character: ' + str(c))
		pixels.append(line)
	for point in path:
		x, y = point
		pixels[x][y] = RED
	for point in path_oppo:
		x, y = point
		pixels[x][y] = GREEN
	result = [[BORDER] * (m * SQUARE_SIZE + m + 1)]
	for row in pixels:
		line = [BORDER]
		for pix in row:
			line.extend([pix] * SQUARE_SIZE)
			line.append(BORDER)
		for j in range(SQUARE_SIZE):
			result.append(line)
		result.append([BORDER] * (m * SQUARE_SIZE + m + 1))
	return result

def save_result(game_map, path, path_oppo=[]):
	pix = convert_array_to_pixel(game_map, path, path_oppo)
	image = Image.fromarray(asarray(pix, dtype=uint8), 'RGBA')
	image.save('result.png')

def load_map(pic):
	im = Image.open(pic)
	pix = im.load()
	width, height = im.size
	if (width - 1) % (SQUARE_SIZE + LINE_WIDTH) != 0 or (height - 1) % (SQUARE_SIZE + LINE_WIDTH) != 0:
		raise RuntimeError('The picture cannot be recoginsed')
	n, m = (height - 1) // (SQUARE_SIZE + LINE_WIDTH), (width - 1) // (SQUARE_SIZE + LINE_WIDTH)
	start_x, x_step = SQUARE_SIZE // 2, SQUARE_SIZE + LINE_WIDTH
	start_y, y_step = SQUARE_SIZE // 2, SQUARE_SIZE + LINE_WIDTH
	game_map = []
	for y in range(start_y, height, y_step):
		row = []
		for x in range(start_x, width, x_step):
			if pix[x, y] == GRAY:
				row.append('g')
			elif pix[x, y] == BLUE:
				row.append('b')
			elif pix[x, y] == YELLOW:
				row.append('y')
			elif pix[x, y] == WHITE:
				row.append('w')
			else:
				print(pix[x, y])
		game_map.append(row)
	return game_map
