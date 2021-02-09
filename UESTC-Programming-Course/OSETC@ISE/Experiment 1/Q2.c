#include <stdio.h>

int main()
{
	int x;
	printf("Enter a dollar amount: \n");
	scanf("%d",&x);
	printf("$20 bills: %d\n",x/20);x=x-(x/20)*20;
	printf("$10 bills: %d\n",x/10);x=x-(x/10)*10;
	printf(" $5 bills: %d\n",x/5);x=x-(x/5)*5;
	printf(" $1 bills: %d\n",x);
	return 0;
}
