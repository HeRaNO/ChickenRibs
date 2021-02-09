#include <stdio.h>

int main()
{
	puts("Enter a number: ");
	int n;scanf("%d",&n);printf("The reversal is: ");
	while (n){printf("%d",n%10);n/=10;}
	puts("");
	return 0;
}
