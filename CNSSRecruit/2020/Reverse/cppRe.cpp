#include <cstdio>

int a[]={81,44,47,83,85,84,4,2,84,3,4,80,82,80,47,4,2,85,82,2,1,44,31,4,44,83,47,31,31,4,82,45};

int main(int argc, char const *argv[])
{
	for (int i:a) putchar((i^0x6F)-10);
	putchar('\n');
	return 0;
}