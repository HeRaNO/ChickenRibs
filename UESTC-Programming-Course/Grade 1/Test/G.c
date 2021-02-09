#include <stdio.h>

int main()
{
	double ans=0.0,a=2,b=1;int i,n;
	puts("please input the number of items: ");
	scanf("%d",&n);
	for (i=1;i<=n;i++)
	{
		ans+=a/b;
		double c=a;a+=b;b=c;
	}
	printf("The sum is: %.5lf\n",ans);
	return 0;
}