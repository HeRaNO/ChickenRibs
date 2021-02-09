#include <math.h>
#include <stdio.h>

int main()
{
	double a,b,c,p,s;
	printf("Enter 3 sides of the triangle: ");
	scanf("%lf %lf %lf",&a,&b,&c);
	if ((a+b>c)&&(a+c>b)&&(b+c>a))
	{
		p=(a+b+c)/2.0;s=sqrt(p*(p-a)*(p-b)*(p-c));
		printf("area=%.2lf;perimeter=%.2lf\n",s,a+b+c);
	}
	else puts("These sides do not correspond to a valid triangle");
	return 0;
}
