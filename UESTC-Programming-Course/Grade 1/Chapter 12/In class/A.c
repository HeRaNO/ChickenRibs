#include <stdio.h>

int main()
{
	int f[15]={0,1},*p;
	for (p=f+2;p<f+15;p++) *p=*(p-1)+*(p-2);
	printf("%d",*f);
	for (p=f+1;p<f+15;p++) printf("%6d",*p);
	putchar('\n');
	return 0;
}
