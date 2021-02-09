#include <stdio.h>

int gcd(int a,int b){return !b?a:gcd(b,a%b);}

int main()
{
	puts("Enter a fraction:");
	int a,b;scanf("%d/%d",&a,&b);
	int t=gcd(a,b);
	printf("In lowest terms: %d/%d\n",a/t,b/t);
	return 0;
}
