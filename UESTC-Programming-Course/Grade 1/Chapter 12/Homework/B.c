#include <stdio.h>

double inner_product(const double p[],const double q[],int n)
{
	int i;double r=0.0;
	for (i=0;i<n;i++) r+=(*(p+i))*(*(q+i));
	return r;
}

int main()
{
	double a[5],b[5];int i;
	puts("Enter 5 numbers for the first array:");
	for (i=0;i<5;i++) scanf("%lf",a+i);
	puts("Enter 5 numbers for the second array:");
	for (i=0;i<5;i++) scanf("%lf",b+i);
	printf("The inner product: %lf\n",inner_product(a,b,5));
	return 0;
}
