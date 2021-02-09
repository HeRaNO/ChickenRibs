#include <stdio.h>

int main(int argc, char const *argv[])
{
	int i;
	if (argc==1) return 0;
	printf("%s",argv[1]);
	for (i=2;i<argc;i++) printf(" %s",argv[i]);putchar('\n');
	return 0;
}
