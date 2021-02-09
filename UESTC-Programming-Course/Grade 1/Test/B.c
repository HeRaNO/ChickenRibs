#include <stdio.h>

void find_two_largest(int a[],int **mx,int **smx)
{
	int i;
	if (a[0]>a[1]){*mx=&a[0];*smx=&a[1];}
	else {*smx=&a[0];*mx=&a[1];}
	for (i=2;i<10;i++)
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
	int i,a[10],*mx,*smx;
	puts("Please input 10 integers: ");
	for (i=0;i<10;i++) scanf("%d",&a[i]);
	find_two_largest(a,&mx,&smx);
	printf("The largest:%d\n",*mx);
	printf("The index of the largest:%ld\n",mx-a);
	printf("The second largest:%d\n",*smx);
	printf("The index of the second largest:%ld\n",smx-a);
	return 0;
}