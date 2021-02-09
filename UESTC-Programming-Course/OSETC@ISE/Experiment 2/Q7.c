#include <stdio.h>

int main()
{
	int x,i;
	printf("Enter a number: ");
	scanf("%d",&x);
	for (i=2;i*i<=x;i+=2) printf("%d\n",i*i);
	return 0;
}