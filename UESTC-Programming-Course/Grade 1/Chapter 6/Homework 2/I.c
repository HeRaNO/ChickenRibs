#include <stdio.h>

int main()
{
	/*
	puts("153    370    371    407");
	return 0;
	*/
	int f=1,i,j,k;
	for (i=1;i<=9;i++)
		for (j=0;j<=9;j++)
			for (k=0;k<=9;k++)
				if (i*i*i+j*j*j+k*k*k==100*i+10*j+k)
				{
					if (f){printf("%d%d%d",i,j,k);f=0;}
					else printf("    %d%d%d",i,j,k);
				}
	puts("");
	return 0;
}
