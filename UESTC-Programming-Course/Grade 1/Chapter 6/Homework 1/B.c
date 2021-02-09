#include <stdio.h>

int gcd(int a,int b){return !b?a:gcd(b,a%b);}

int main()
{
	puts("Enter two integers:");
	int a,b;scanf("%d %d",&a,&b);
	printf("Greatest common divisor: %d\n",gcd(a,b));
	return 0;
}
