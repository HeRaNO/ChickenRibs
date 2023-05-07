#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

int sgn(int x)
{
	return !x ? 0 : (x < 0 ? -1 : 1);
}

struct Point
{
	int x, y;
	Point() {}
	Point(int _x, int _y): x(_x), y(_y) {}
	Point operator - (const Point &p) const {
		return Point(x - p.x, y - p.y);
	}
	int operator * (const Point &p) const {
		return x * p.y - y * p.x;
	}
	bool operator < (const Point &p) const {
		return x == p.x ? y < p.y : x < p.x;
	}
};

int ccw(Point A, Point B, Point C)
{
	return sgn(A * B + B * C + C * A);
}

std::vector<Point> merge(const std::vector<Point> &lch, const std::vector<Point> &rch)
{
	int n = lch.size(), m = rch.size();
	int p = std::max_element(lch.begin(), lch.end()) - lch.begin();
	int q = std::min_element(rch.begin(), rch.end()) - rch.begin();
	int cp_p = p, cp_q = q; bool f = false;
	while (!f)
	{
		f = true;
		while (n > 1 && ccw(rch[q], lch[p], lch[(p + 1) % n]) >= 0)
		{
			if (ccw(rch[q], lch[p], lch[(p + 1) % n]) == 0
				&& (lch[p].y > lch[(p + 1) % n].y || (lch[p].y == lch[(p + 1) % n].y && lch[p].x <= lch[(p + 1) % n].x)))
				break;
			p = (p + 1) % n;
		}
		while (m > 1 && ccw(lch[p], rch[q], rch[(q - 1 + m) % m]) <= 0)
		{
			if (ccw(lch[p], rch[q], rch[(q - 1 + m) % m]) == 0
				&& (rch[q].y > rch[(q - 1 + m) % m].y || (rch[q].y == rch[(q - 1 + m) % m].y && rch[q].x >= rch[(q - 1 + m) % m].x)))
				break;
			q = (q - 1 + m) % m;
			f = false;
		}
	}
	int upper_p = p, upper_q = q;
	p = cp_p, q = cp_q; f = false;
	while (!f)
	{
		f = true;
		while (m > 1 && ccw(lch[p], rch[q], rch[(q + 1) % m]) >= 0)
		{
			if (ccw(lch[p], rch[q], rch[(q + 1) % m]) == 0
				&& (rch[q].y < rch[(q + 1) % m].y || (rch[q].y == rch[(q + 1) % m].y && rch[q].x >= rch[(q + 1) % m].x)))
				break;
			q = (q + 1) % m;
		}
		while (n > 1 && ccw(rch[q], lch[p], lch[(p - 1 + n) % n]) <= 0)
		{
			if (ccw(rch[q], lch[p], lch[(p - 1 + n) % n]) == 0
				&& (lch[p].y < lch[(p - 1 + n) % n].y || (lch[p].y == lch[(p - 1 + n) % n].y && lch[p].x <= lch[(p - 1 + n) % n].x)))
				break;
			p = (p - 1 + n) % n;
			f = false;
		}
	}
	int lower_p = p, lower_q = q;
	std::vector<Point> res;
	int i = upper_p;
	while (true)
	{
		res.push_back(lch[i]);
		if (i == lower_p) break;
		i = (i + 1) % n;
	}
	i = lower_q;
	while (true)
	{
		res.push_back(rch[i]);
		if (i == upper_q) break;
		i = (i + 1) % m;
	}
	return res;
}

std::vector<Point> DC(const std::vector<Point> &P, int l, int r)
{
	if (l + 1 == r) return std::vector<Point>{P[l]};
	int m = l + r >> 1;
	std::vector<Point> lch = DC(P, l, m);
	std::vector<Point> rch = DC(P, m, r);
	return merge(lch, rch);
}

int main()
{
	int n; scanf("%d", &n);
	std::vector<Point> p(n);
	for (int i = 0; i < n; i++)
	{
		int x, y; scanf("%d %d", &x, &y);
		p[i] = Point(x, y);
	}
	sort(p.begin(), p.end());
	std::vector<Point> ch = DC(p, 0, n);
	printf("%d\n", (int)ch.size());
	for (Point p : ch) printf("%d %d\n", p.x, p.y);
	return 0;
}