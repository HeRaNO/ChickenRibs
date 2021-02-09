#include <stdio.h>
#include <stdlib.h>

int main()
{
	puts("Please input the upper bound: ");
	int n,i,a=0,b=0;scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		if (i&1) a+=i;
		else b+=i;
	}
	printf("Sum of odds: %d\n",a);
	printf("Sum of evens: %d\n",b);
	printf("Absolute Difference: %d\n",abs(a-b));
	return 0;
}
