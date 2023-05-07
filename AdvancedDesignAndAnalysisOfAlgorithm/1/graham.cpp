#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>

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
	int ptr_p0 = 0;
	for (int i = 0; i < n; i++)
	{
		int x, y; scanf("%d %d", &x, &y);
		p[i] = Point(x, y);
		if (y < p[ptr_p0].y)
			ptr_p0 = i;
		else if (y == p[ptr_p0].y && x < p[ptr_p0].x)
			ptr_p0 = i;
	}
	std::vector<std::pair<Point, Point>> v;
	for (int i = 0; i < n; i++)
	{
		if (i == ptr_p0) continue;
		v.push_back({p[i] - p[ptr_p0], p[i]});
	}
	sort(v.begin(), v.end(), [&](std::pair<Point, Point> a, std::pair<Point, Point> b){
		int s = a.first * b.first;
		return s ? s > 0 : a.first.length() < b.first.length();
	});
	std::vector<Point> ch;
	ch.push_back(p[ptr_p0]);
	for (auto [_, p] : v)
	{
		while (ch.size() > 1 && (ch.back() - ch[ch.size() - 2]) * (p - ch[ch.size() - 2]) <= 0)
			ch.pop_back();
		ch.push_back(p);
	}
	printf("%d\n", (int)ch.size());
	for (Point p : ch) printf("%d %d\n", p.x, p.y);
	return 0;
}
