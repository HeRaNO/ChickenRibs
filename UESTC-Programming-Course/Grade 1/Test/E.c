#include <stdio.h>

void find(int a[3][4],int *pr,int *pc,int *qr,int *qc)
{
	int i,j;
	for (i=0;i<3;i++)
		for (j=0;j<4;j++)
		{
			if (a[i][j]>a[*pr][*pc]){*pr=i;*pc=j;}
			if (a[i][j]<a[*qr][*qc]){*qr=i;*qc=j;}
		}
	return ;
}

int main()
{
	int i,j,mxr=0,mxc=0,mnr=0,mnc=0,a[3][4];
	puts("please input 3*4 integers:");
	for (i=0;i<3;i++)
		for (j=0;j<4;j++)
			scanf("%d",&a[i][j]);
	find(a,&mxr,&mxc,&mnr,&mnc);
	printf("max=%d,row=%d,col=%d\n",a[mxr][mxc],mxr,mxc);
	printf("min=%d,row=%d,col=%d\n",a[mnr][mnc],mnr,mnc);
	return 0;
}