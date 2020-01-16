#include <cmath>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <graphics.h>
using namespace std;

const double k = 8987551787.9979;

struct Electronic
{
	double x, y, q;
	Electronic(){}
	Electronic(double _x, double _y, double _q):
		x(_x), y(_y), q(_q){}
};

/*
theta = atan2(y-yi,x-xi)
Ex = kq/(r^2) cos theta
Ey = kq/(r^2) sin theta
r = sqrt((x-xi)^2+(y-yi)^2)
*/

double left_x, left_y, right_x, right_y, eps;
vector <Electronic> e, pic;

Electronic calculateElectricField(int n)
{
	double Ex, Ey, maxE = 0.0, r_2, theta; int dx = 0, dy = 0;
	for (double x = left_x; x <= right_x; x += eps, ++dx)
	{
		dy = 0;
		for (double y = left_y; y <= right_y; y += eps, ++dy)
		{
			Ex = 0.0; Ey = 0.0;
			for (int i = 0; i < n; ++i)
			{
				if (fabs(e[i].x - x) < eps && fabs(e[i].y - y) < eps)
				{
					Ex = 0.0;
					Ey = 0.0;
					break;
				}
				theta = atan2(y - e[i].y, x - e[i].x);
				r_2 = (x - e[i].x) * (x - e[i].x) + (y - e[i].y) * (y - e[i].y);
				Ex += k * e[i].q / r_2 * cos(theta);
				Ey += k * e[i].q / r_2 * sin(theta);
			}
			maxE = max(maxE, sqrt(Ex * Ex + Ey * Ey));
			pic.push_back(Electronic(dx, dy, sqrt(Ex * Ex + Ey * Ey)));
		}
	}
	return Electronic(dx, dy, maxE);
}

void drawElectricField(Electronic r)
{
	initgraph(r.x, r.y);
	PIMAGE h = newimage(r.x, r.y); double maxE = r.q;
	for (int i = 0; i < (int)pic.size(); i++)
	{
		int color = pic[i].q / maxE * 16777216.0;
		int b = color % 256;
		int g = color / 256 % 256;
		int r = color / 65536;
		putpixel(pic[i].x, pic[i].y, EGERGB(r, g, b), h);
	}
	savepng(h, "e.png");
	return ;
}

int main()
{
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		double a, b, c;
		scanf("%lf %lf %lf", &a, &b, &c);
		e.push_back(Electronic(a, b, c));
	}
	scanf("%lf %lf %lf %lf %lf", &left_x, &left_y, &right_x, &right_y, &eps);
	Electronic mx = calculateElectricField(n);
	drawElectricField(mx);
	return 0;
}
