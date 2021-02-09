#include <stdio.h>

int main()
{
	int i,j,c,a[4][4];
	printf("Enter the numbers from 1 to 16 in any order:\n");
	puts("");
	for (i=0;i<16;i++) scanf("%d",&a[i/4][i%4]);
	for (i=0;i<4;i++)
		for (j=0;j<4;j++)
			printf("%3d%c",a[i][j],j==3?'\n':' ');
	printf("\nRow sums: ");
	for (i=0;i<4;i++)
	{
		c=0;
		for (j=0;j<4;j++) c+=a[i][j];
		printf("%4d",c);
	}
	printf("\nColumn sums: ");
	for (i=0;i<4;i++)
	{
		c=0;
		for (j=0;j<4;j++) c+=a[j][i];
		printf("%4d",c);
	}
	printf("\nDiagonal sums: ");
	c=0;
	for (i=0;i<4;i++) c+=a[i][i];
	printf("%4d",c);
	c=0;
	for (i=0;i<4;i++) c+=a[3-i][i];
	printf("%4d\n",c);
	return 0;
}
