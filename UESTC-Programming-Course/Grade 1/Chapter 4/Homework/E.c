#include <stdio.h>

char a[15];

int main()
{
	printf("Enter the first 11 digits of a UPC:\n");
	scanf("%s",a);
	int x=a[0]+a[2]+a[4]+a[6]+a[8]+a[10]-288;
	int y=a[1]+a[3]+a[5]+a[7]+a[9]-240;
	x*=3;x+=y;x=(x-1)%10;x=9-x;
	printf("Check digit: %d\n",x);
	return 0;
}
