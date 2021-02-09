#include <stdio.h>

double a[10];
int n,f=1;

void get_data()
{
	while (~scanf("%lf",&a[n])) ++n;
	return ;
}

double harmonic_array()
{
	int i;double x=0.0;
	for (i=0;i<n;i++) x+=1.0/a[i];
	return n/x;
}

int main()
{
	printf("Please input less than 10 double numbers:\n");
	get_data();
	printf("The harmonic mean of this array is: %.5lf\n",harmonic_array());
	return 0;
}