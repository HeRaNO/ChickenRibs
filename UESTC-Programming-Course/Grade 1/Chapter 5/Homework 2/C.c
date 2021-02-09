#include <stdio.h>

int main()
{
	puts("Enter four integers:");
	int a,b,c,d;
	scanf("%d %d %d %d",&a,&b,&c,&d);
	if (a<b){int t=a;a=b;b=t;}
	if (c<d){int t=c;c=d;d=t;}
	if (a>c) printf("Largest: %d\n",a);
	else printf("Largest: %d\n",c);
	if (b<d) printf("Smallest: %d\n",b);
	else printf("Smallest: %d\n",d);
	return 0;
}
