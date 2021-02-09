#include <stdio.h>

int main()
{
	int x,y;
	printf("Enter an integer: \n");
	scanf("%d",&x);
	y=3*x*x*x*x*x+2*x*x*x*x-5*x*x*x-x*x+7*x-6;
	printf("The result is:%d\n",y);
	return 0;
}
