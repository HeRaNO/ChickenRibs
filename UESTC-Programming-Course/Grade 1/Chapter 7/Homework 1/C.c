#include <stdio.h>

double x,p;

int main()
{
	puts("This program sums a series of double values.");
	puts("Enter values (0 to terminate): ");
	while (~scanf("%lf",&x)&&x!=0.0) p+=x;
	printf("The sum is: %g\n",p);
	return 0;
}
