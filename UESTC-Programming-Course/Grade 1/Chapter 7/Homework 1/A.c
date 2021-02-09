#include <math.h>
#include <stdio.h>

double x,mx=-1e18,mn=1e18,s,p,avg;
int n;

void max(double x){if (mx<x) mx=x;return ;}
void min(double x){if (mn>x) mn=x;return ;}

int main()
{
	puts("Enter a series numbers:");
	while (~scanf("%lf",&x)&&x!=0.0)
	{
		max(x);min(x);s+=x;p+=x*x;++n;
	}
	avg=s/n;
	printf("smallest:%g\n",mn);
	printf("largest:%g\n",mx);
	printf("average:%g\n",avg);
	printf("standard_deviation:%g\n",sqrt(p/n-avg*avg));
	return 0;
}
