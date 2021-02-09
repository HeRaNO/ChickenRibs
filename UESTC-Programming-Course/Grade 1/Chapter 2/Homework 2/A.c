#include <stdio.h>

int main()
{
	double a,b,c;
	printf("Enter amount of loan:\n");
	scanf("%lf",&a);
	printf("Enter interest rate:\n");
	scanf("%lf",&b);b/=100;b/=12;
	printf("Enter monthly payment:\n");
	scanf("%lf",&c);
	a+=a*b;a-=c;
	printf("Balance remaining after first payment: $%.2lf\n",a);
	a+=a*b;a-=c;
	printf("Balance remaining after second payment: $%.2lf\n",a);
	a+=a*b;a-=c;
	printf("Balance remaining after third payment: $%.2lf\n",a);
	return 0;
}
