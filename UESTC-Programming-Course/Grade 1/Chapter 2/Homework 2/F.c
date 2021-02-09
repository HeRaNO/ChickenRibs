#include <stdio.h>

int main()
{
	double r;
	printf("Enter an amount:\n");
	scanf("%lf",&r);
	printf("With tax added:$%.2lf\n",1.05*r);
	return 0;
}
