#include <stdio.h>

char a[3],b[5],c[5],d[15];

int main()
{
	printf("Enter the first (single) digit:\n");
	scanf("%s",a);
	printf("Enter first group of five digits:\n");
	scanf("%s",b);
	printf("Enter second group of five digits:\n");
	scanf("%s",c);
	int x=a[0]+b[1]+b[3]+c[0]+c[2]+c[4]-288;
	int y=b[0]+b[2]+b[4]+c[1]+c[3]-240;
	x*=3;x+=y;x=(x-1)%10;x=9-x;
	printf("Check digit: %d\n",x);
	return 0;
}
