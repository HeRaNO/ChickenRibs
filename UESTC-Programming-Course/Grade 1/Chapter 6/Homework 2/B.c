#include <stdio.h>

int main(int argc, char const *argv[])
{
	unsigned long long x=~(1ULL<<64);
	printf("volume: %.7g\n",(double)x/1.42e8);
	return 0;
}
