#include <stdio.h>

int gcd(int a,int b){return !b?a:gcd(b,a%b);}

int main()
{
	int a,b;
	printf("Enter two integers: ");
	scanf("%d %d",&a,&b);
	printf("Greatest common divisor: %d\n",gcd(a,b));
	return 0;
}