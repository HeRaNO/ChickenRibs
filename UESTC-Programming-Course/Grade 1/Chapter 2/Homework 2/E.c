#include <stdio.h>

int main()
{
	double r;
	printf("Please input the radius:\n");
	scanf("%lf",&r);
	printf("The volume is:%.2lf\n",(4.0/3.0)*3.14*r*r*r);
	return 0;
}
