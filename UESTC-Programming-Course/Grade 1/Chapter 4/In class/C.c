#include <math.h>
#include <stdio.h>

int main()
{
	double a,b,c,p;
	puts("Please input data:");puts("");
	scanf("%lf%lf%lf",&a,&b,&c);p=(a+b+c)/2.0;
	printf("area=%.3lf\n",sqrt(p*(p-a)*(p-b)*(p-c)));
	return 0;
}
