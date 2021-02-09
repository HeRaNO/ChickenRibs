#include <stdio.h>

void find_two_largest(int a[],int n,int **mx,int **smx)
{
	int i;
	if (a[0]>a[1]){*mx=&a[0];*smx=&a[1];}
	else {*mx=&a[1];*smx=&a[0];}
	for (i=2;i<n;i++)
	{
		if (a[i]>**mx)
		{
			*smx=*mx;
			*mx=&a[i];
		}
		else if (a[i]>**smx) *smx=&a[i];
	}
	return ;
}

int main()
{
	int a[10],i,*p,*q;
	puts("Please input 10 integers: ");
	for (i=0;i<10;i++) scanf("%d",&a[i]);
	find_two_largest(a,10,&p,&q);
	printf("The largest:%d\n",*p);
	printf("The index of the largest:%d\n",p-a);
	printf("The second largest:%d\n",*q);
	printf("The index of the second largest:%d\n",q-a);
	return 0;
}
