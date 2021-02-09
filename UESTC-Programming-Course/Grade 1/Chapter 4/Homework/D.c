#include <stdio.h>

int main()
{
	printf("Enter a number between 0 and 32767:\n");
	int x;scanf("%d",&x);
	printf("In octal, your number is: %05o\n",x);
	return 0;
}
