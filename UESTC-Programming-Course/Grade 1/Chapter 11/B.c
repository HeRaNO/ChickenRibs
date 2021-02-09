#include <stdio.h>

void find_two_largest(int a[],int n,int *mx,int *mn)
{
	int i;*mx=1<<31;*mn=1<<31;
	for (i=0;i<n;i++)
	{
		if (*mx<a[i])
		{
			*mn=*mx;*mx=a[i];
		}
		else if (*mn<a[i]) *mn=a[i];
	}
	return ;
}

int main()
{
	int a[10],mx,smx,i;
	printf("Enter 10 integers:\n");
	for (i=0;i<10;i++) scanf("%d",&a[i]);
	find_two_largest(a,10,&mx,&smx);
	printf("Largest: %d\n",mx);
	printf("Second Largest: %d\n",smx);
	return 0;
}
