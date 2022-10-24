#include <cstdio>
#include <algorithm>

char s[40];

int main(int argc, char const *argv[])
{
	*(unsigned long long *)s = 7233170650472790326LL;
	*(((unsigned int *)s)+2) = 892494177;
	*(((unsigned short *)s)+6) = 26209;
	*(((unsigned short *)s)+7) = 25906;
	*(((unsigned long long *)s)+2) = 3617296709725664100LL;
	std::reverse(s+16,s+16+8);
	*(((unsigned int *)s)+6) = 959527220;
	std::reverse(s+24,s+24+4);
	*(((unsigned short *)s)+14) = 13104;
	std::reverse(s+28,s+28+2);
	*(((unsigned short *)s)+15) = 12643;
	std::reverse(s+30,s+30+2);
	puts(s);
	return 0;
}