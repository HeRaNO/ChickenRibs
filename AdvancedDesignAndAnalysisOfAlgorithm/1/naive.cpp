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
	int length() const {
		return x * x + y * y;
	}
};

int main()
{
	int n; scanf("%d", &n);
	std::vector<Point> p(n);
	for (int i = 0; i < n; i++)
	{
		double x, y; scanf("%lf %lf", &x, &y);
		p[i] = Point(x, y);
	}
	std::vector<bool> on_convex_hull(n, false);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			if (i == j) continue;
			Point l = p[j] - p[i]; bool f = true;
			for (Point pt : p)
				if (sgn((pt - p[i]) * l) > 0)
				{
					f = false;
					break;
				}
			if (f)
			{
				on_convex_hull[i] = true;
				on_convex_hull[j] = true;
			}
		}
	int ptr_p0 = 0;
	for (int i = 0; i < n; i++)
		if (on_convex_hull[i])
		{
			if (p[i].y < p[ptr_p0].y)
				ptr_p0 = i;
			else if (p[i].y == p[ptr_p0].y && p[i].x < p[ptr_p0].x)
				ptr_p0 = i;
		}
	std::vector<std::pair<Point, Point>> v;
	for (int i = 0; i < n; i++)
	{
		if (i == ptr_p0 || !on_convex_hull[i]) continue;
		v.push_back({p[i] - p[ptr_p0], p[i]});
	}
	sort(v.begin(), v.end(), [&](std::pair<Point, Point> a, std::pair<Point, Point> b){
		int s = sgn(a.first * b.first);
		return s ? s > 0 : a.first.length() < b.first.length();
	});
	std::vector<Point> ch;
	ch.push_back(p[ptr_p0]);
	for (auto [_, p] : v)
	{
		if (ch.size() > 1 && (ch.back() - ch[ch.size() - 2]) * (p - ch[ch.size() - 2]) == 0)
			ch.pop_back();
		ch.push_back(p);
	}
	printf("%d\n", (int)ch.size());
	for (Point p : ch) printf("%d %d\n", p.x, p.y);
	return 0;
}