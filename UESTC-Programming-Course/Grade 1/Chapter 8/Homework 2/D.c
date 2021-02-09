#include <stdio.h>

int main()
{
	int a[5][5],i,j,s,mx,mn;
	for (i=0;i<5;i++)
	{
		printf("Enter grades for student %d:\n",i+1);
		for (j=0;j<5;j++) scanf("%d",&a[i][j]);
	}
	puts("Student Total Average");
	for (i=0;i<5;i++)
	{
		s=0;
		for (j=0;j<5;j++) s+=a[i][j];
		printf("%d%6d%6d\n",i+1,s,s/5);
	}
	puts("\nQuiz Average High Low");
	for (i=0;i<5;i++)
	{
		s=0;mx=-1;mn=101;
		for (j=0;j<5;j++)
		{
			s+=a[j][i];
			if (mx<a[j][i]) mx=a[j][i];
			if (mn>a[j][i]) mn=a[j][i];
		}
		printf("%d%6d%6d%6d\n",i+1,s/5,mx,mn);
	}
	return 0;
}
