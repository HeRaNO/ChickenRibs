#include <stdio.h>

int main()
{
	int f[15],i;
	f[0]=0;f[1]=1;
	for (i=2;i<15;i++) *(f+i)=*(f+i-1)+(*(f+i-2));
	for (i=0;i<15;i++) printf("%6d",*(f+i));
	puts("");
	return 0;
}