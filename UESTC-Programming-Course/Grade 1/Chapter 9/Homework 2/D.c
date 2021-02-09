#include <stdio.h>

void QuickSort(int a[],int l,int r)
{
	if (l>=r) return ;
	int p=a[l],pl=l,pr=r;
	while (l<r)
	{
		while (l<r&&p<=a[r]) --r;if (l<r) a[l++]=a[r];
		while (l<r&&a[l]< p) ++l;if (l<r) a[r--]=a[l];
	}
	a[l]=p;QuickSort(a,pl,l-1);QuickSort(a,l+1,pr);
	return ;
}

int main()
{
	int n=10,p[11],i;
	puts("Enter 10 numbers to be sorted: ");
	for (i=1;i<=n;i++) scanf("%d",&p[i]);
	QuickSort(p,1,n);
	printf("In sorted order:");
	for (i=1;i<=n;i++) printf(" %d",p[i]);putchar('\n');
	return 0;
}
