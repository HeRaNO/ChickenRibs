#include <stdio.h>

int main()
{
	float a,b,c;
	printf("Enter amount of loan: ");
	scanf("%f",&a);
	printf("Enter interest rate: ");
	scanf("%f",&b);b/=100;b/=12;
	printf("Enter monthly payment: \n");
	scanf("%f",&c);
	a=a*(b+1.0f);a-=c;
	printf("Balance remaining after first payment: $%.2f\n",a);
	a=a*(b+1.0f);a-=c;
	printf("Balance remaining after second payment: $%.2f\n",a);
	a=a*(b+1.0f);a-=c;
	printf("Balance remaining after third payment: $%.2f\n",a);
	return 0;
}
