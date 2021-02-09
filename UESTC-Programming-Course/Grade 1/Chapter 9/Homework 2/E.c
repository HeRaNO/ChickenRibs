#include <stdio.h>

int mpow(int x,int n){return n==1?x:mpow(x,n-1)*x;}

int main()
{
	int a,b;scanf("%d %d",&a,&b);
	printf("mypower(%d,%d):  %d\n",a,b,mpow(a,b));
	return 0;
}