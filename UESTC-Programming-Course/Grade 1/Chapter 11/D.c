#include <math.h>
#include <stdio.h>

int separate(double a,int *i,double *f)
{
	*i=fabs(a);*f=fabs(a)-(double)*i;
	if (a<0) return -1;
	else if (a==0) return 0;
	else return 1;
}

int main()
{
	printf("Enter a number: \n");
	printf("sign: ");
	double a,f;int p,i;
	scanf("%lf",&a);
	p=separate(a,&i,&f);
	if (p==-1) putchar('-');
	else if (!p) putchar(' ');
	else putchar('+');
	putchar('\n');
	printf("integer part: %d\n",i);
	printf("fractional part: %lg\n",f);
	return 0;
}