from io_map import load_map, save_result
from queue import PriorityQueue
from blocks import AreaBlock, Q_2

DIR =[
	(0, 1, Q_2(1, 0)), (0, -1, Q_2(1, 0)),
	(1, 0, Q_2(1, 0)), (-1, 0, Q_2(1, 0)),
	(1, 1, Q_2(0, 1)), (1, -1, Q_2(0, 1)),
	(-1, -1, Q_2(0, 1)), (-1, 1, Q_2(0, 1))
]

def get_land_cost(kind):
	return {'y': 4, 'b': 2, 'g': -1, 'w': 0}[kind]

def get_dis(A, B):
	a, b = A
	c, d = B
	x, y = abs(a - c), abs(b - d)
	if x < y:
		x, y = y, x
	return Q_2(x - y, y)

def calc_f(now, tar):
	return now.g + get_dis(now.get_coordinate(), tar.get_coordinate())

def out_of_bound(x, y, n, m):
	if x < 0 or x >= n:
		return True
	if y < 0 or y >= m:
		return True
	return False

def find_path(ed):
	path = []
	while ed is not None:
		path.append(ed.get_coordinate())
		ed = ed.fr
	return path

def search_one_way(g_mp, st_pos, ed_pos):
	n, m = len(mp), len(mp[0])
	open_table = PriorityQueue()
	gScore = {}
	st_pos.f = calc_f(st_pos, ed_pos)
	open_table.put(st_pos)
	gScore[st_pos.get_coordinate()] = Q_2(0, 0)
	while not open_table.empty():
		now = open_table.get()
		now_x, now_y = now.get_coordinate()
		if (now_x, now_y) == ed_pos.get_coordinate():
			print(now.g)
			return find_path(now)
		for dx, dy, move_cost in DIR:
			nxt_x, nxt_y = now_x + dx, now_y + dy
			if out_of_bound(nxt_x, nxt_y, n, m):
				continue
			land_cost = get_land_cost(g_mp[nxt_x][nxt_y])
			if land_cost == -1:
				continue
			nxt = AreaBlock(fr=now,
							g=now.g+move_cost+Q_2(land_cost, 0),
							x=nxt_x, y=nxt_y)
			gNxt = gScore.get((nxt_x, nxt_y))
			if gNxt is None or nxt.g < gNxt:
				gScore[(nxt_x, nxt_y)] = nxt.g
				nxt.f = calc_f(nxt, ed_pos)
				tmp_q = [nxt]
				while not open_table.empty():
					tmp = open_table.get()
					if tmp.get_coordinate() == (nxt_x, nxt_y):
						break
					tmp_q.append(tmp)
				for tmp in tmp_q:
					open_table.put(tmp)
	return None

if __name__ == "__main__":
	st = AreaBlock(fr=None, x=8, y=3)
	ed = AreaBlock(fr=None, x=9, y=14)
	mp = load_map('map1.png')
	# st = AreaBlock(fr=None, x=10, y=4)
	# ed = AreaBlock(fr=None, x=0, y=35)
	# mp = load_map('map2.png')
	path = search_one_way(mp, st, ed)
	if path is None:
		print("doesn't exist path")
	else:
		save_result(mp, path)
