#include <stdio.h>

int main()
{
	puts("Enter an positive integer:");
	int n,a=0;scanf("%d",&n);
	printf("The digits are:");
	while (n){printf("   %d",n%10);a+=n%10;n/=10;}
	puts("");
	if (a%9) puts("Divisible by 9: NO.");
	else puts("Divisible by 9: YES.");
	return 0;
}
