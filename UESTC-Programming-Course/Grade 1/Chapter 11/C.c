#include <stdio.h>

int *find_largest(int a[],int n)
{
	int i;int *mx=&a[0];
	for (i=0;i<n;i++) if (*mx<a[i]) mx=&a[i];
	return mx;
}

int main()
{
	int a[10],i;int *p;
	printf("Enter 10 integers:\n");
	for (i=0;i<10;i++) scanf("%d",&a[i]);
	p=find_largest(a,10);
	printf("The largest: %d\n",*p);
	return 0;
}
