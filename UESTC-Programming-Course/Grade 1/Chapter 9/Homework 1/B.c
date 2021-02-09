#include <stdio.h>

double f(double x)
{
	return 3*x*x*x*x*x
		  +2*x*x*x*x
		  -5*x*x*x
		  -x*x
		  +7*x
		  -6;
}

int main()
{
	double x;
	puts("Enter value for x: ");
	scanf("%lf",&x);
	printf("Polynomial value: %g\n",f(x));
	return 0;
}
