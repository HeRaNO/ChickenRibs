#include <stdio.h>

void Pass(int t,int *h,int *m,int *s)
{
	*h=(t/3600)%24;t%=3600;*m=t/60;t%=60;*s=t;
	return ;
}

int main()
{
	int t,h=0,m=0,s=0;
	printf("Enter total seconds:\n");
	scanf("%d",&t);
	Pass(t,&h,&m,&s);
	printf("Time:\n%d:%d:%d\n",h,m,s);
	return 0;
}
