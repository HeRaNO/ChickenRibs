#include <stdio.h>

void max_min(int a[],int n,int *mx,int *mn)
{
	int i;*mx=1<<31;*mn=~(1<<31);
	for (i=0;i<n;i++)
	{
		if (*mx<a[i]) *mx=a[i];
		if (*mn>a[i]) *mn=a[i];
	}
	return ;
}

int main()
{
	int a[10],mx,mn,i;
	printf("Enter 10 numbers: \n");
	for (i=0;i<10;i++) scanf("%d",&a[i]);
	max_min(a,10,&mx,&mn);
	printf("Largest: %d\n",mx);
	printf("Smallest: %d\n",mn);
	return 0;
}
