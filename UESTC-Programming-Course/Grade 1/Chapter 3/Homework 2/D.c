#include <stdio.h>

int main()
{
	int a,b,c;
	printf("Enter phone number [(xxx) xxx-xxxx]:\n");
	scanf("(%d) %d-%d",&a,&b,&c);
	printf("You entered %03d.%03d.%04d\n",a,b,c);
	return 0;
}
