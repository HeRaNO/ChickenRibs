#include <stdio.h>

int main()
{
	int x,f=0,nx=0;
	puts("Please input an integer: ");
	scanf("%d",&x);
	if (x<0){f=1;x=-x;}
	while (x)
	{
		nx=nx*10+x%10;x/=10;
	}
	if (f) nx=-nx;
	printf("After reversing: %d",nx);
	return 0;
}