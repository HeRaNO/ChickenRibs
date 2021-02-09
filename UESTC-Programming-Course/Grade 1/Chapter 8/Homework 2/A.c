#include <stdio.h>

int main()
{
	int i,j,x,mxx=0,mxy=0,mnx=0,mny=0,mx=1<<31,mn=~(1<<31);
	puts("please input 3*4 integers:");
	for (i=0;i<3;i++)
		for (j=0;j<4;j++)
		{
			scanf("%d",&x);
			if (mx<x)
			{
				mx=x;mxx=i;mxy=j;
			}
			if (mn>x)
			{
				mn=x;mnx=i;mny=j;
			}
		}
	printf("max=%d,row=%d,col=%d\n",mx,mxx,mxy);
	printf("min=%d,row=%d,col=%d\n",mn,mnx,mny);
	return 0;
}
