#include <stdio.h>

int main()
{
	double a,b,c;
	scanf("%lf %lf %lf",&a,&b,&c);
	if (a+b>c&&a+c>b&&b+c>a)
	{
		if (a==b&&b==c) return puts("equilateral triangle"),0;
		if (a==b||a==c||b==c) return puts("isoceles triangle"),0;
		if (a*a+b*b==c*c||a*a+c*c==b*b||b*b+c*c==a*a) return puts("right-angled triangle"),0;
		puts("arbitrary triangle");
	}
	else puts("It isn't triangle.");
	return 0;
}
