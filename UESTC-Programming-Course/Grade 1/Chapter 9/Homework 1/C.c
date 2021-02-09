#include <stdio.h>

double harmonic_mean(double a,double b)
{
	return 2.0/(1.0/a+1.0/b);
}

int main()
{
	double a,b;
	puts("Please input two double numbers: ");
	scanf("%lf %lf",&a,&b);
	printf("The harmonic mean of %g and %g is: %g\n",a,b,harmonic_mean(a,b));
	return 0;
}
