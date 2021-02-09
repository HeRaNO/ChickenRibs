#include <stdio.h>

int main()
{
	double a;
	puts("Enter income:");
	scanf("%lf",&a);
	printf("The tax is: $");
	if (a<=750) printf("%.2lf\n",a*0.01);
	else if (a<=2250) printf("%.2lf\n",(a-750.0)*0.02+7.5);
	else if (a<=3750) printf("%.2lf\n",(a-2250.0)*0.03+37.5);
	else if (a<=5250) printf("%.2lf\n",(a-3750.0)*0.04+82.5);
	else if (a<=7000) printf("%.2lf\n",(a-5250.0)*0.05+142.5);
	else printf("%.2lf\n",(a-7000.0)*0.06+230.0);
	return 0;
}
