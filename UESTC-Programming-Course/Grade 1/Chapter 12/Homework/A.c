#include <stdio.h>

int search(const int a[],int n,int f)
{
	int i;
	for (i=0;i<n;i++) if (a[i]==f) return 1;
	return 0;
}

int main()
{
	int a[5],i,k;
	puts("Enter 5 integers:");
	for (i=0;i<5;i++) scanf("%d",a+i);
	puts("Enter a key:");
	scanf("%d",&k);
	printf("The result: %d\n",search(a,5,k));
	return 0;
}
