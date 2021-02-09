#include <stdio.h>

int main()
{
	char a[3];
	printf("Enter a three-digit number: ");
	scanf("%s",a);
	printf("The reversal is: %c%c%c\n",a[2],a[1],a[0]);
	return 0;
}
