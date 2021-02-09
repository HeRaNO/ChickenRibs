#include <stdio.h>

char a[15];

int main()
{
	printf("Enter the first (single) digit: ");
	printf("Enter first group of five digits: ");
	printf("Enter second group of five digits: ");
	printf("Enter the last (single) digit: ");
	scanf("%s",a);
	scanf("%s",a+1);
	scanf("%s",a+6);
	scanf("%s",a+11);
	int x=a[0]+a[2]+a[4]+a[6]+a[8]+a[10]-288;
	int y=a[1]+a[3]+a[5]+a[7]+a[9]-240;
	x*=3;x+=y;x=(x-1)%10;x=9-x;
	if (x+'0'!=a[11]) puts("NOT VALID");
	else puts("VALID");
	return 0;
}
