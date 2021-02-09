#include <stdio.h>
#include <stdlib.h>

int main()
{
	puts("Please input an integer:\n");
	int n;scanf("%d",&n);
	if (abs(n)<=2) printf("Your number is: %d\n",n);
	else printf("Your number is out of the given range.\n");
	return 0;
}
