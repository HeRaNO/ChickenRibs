#include <stdio.h>

int main()
{
	int i,a[10];
	puts("Enter 10 numbers: ");
	for (i=0;i<10;i++) scanf("%d",&a[i]);
	printf("In reverse order:");
	for (i=9;i>=0;i--) printf(" %d",a[i]);
	putchar('\n');
	return 0;
}
