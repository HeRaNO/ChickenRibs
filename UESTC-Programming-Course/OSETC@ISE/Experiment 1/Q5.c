#include <stdio.h>

int main()
{
	int a,b,c,d,x,y;
	printf("Enter two fractions separated by a plus sign: ");
	scanf("%d/%d+%d/%d",&a,&b,&c,&d);
	x=a*d+b*c;y=b*d;
	printf("The sum is %d/%d\n",x,y);
	return 0;
}
