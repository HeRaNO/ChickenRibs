#include <stdio.h>

int main()
{
	int a[5][5],i,j,s;
	for (i=0;i<5;i++)
	{
		printf("Enter row %d:\n",i+1);
		for (j=0;j<5;j++) scanf("%d",&a[i][j]);
	}
	printf("Row totals:");
	for (i=0;i<5;i++)
	{
		s=0;
		for (j=0;j<5;j++) s+=a[i][j];
		printf("%6d",s);
	}
	puts("");
	printf("Column totals:");
	for (i=0;i<5;i++)
	{
		s=0;
		for (j=0;j<5;j++) s+=a[j][i];
		printf("%6d",s);
	}
	return 0;
}
