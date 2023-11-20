#include <stdio.h>

int main()
{
	char flag[32];
	char cipher[32];
	*(long long *)cipher = 0x731047656E6F7579LL;
	*(long long *)&cipher[8] = 0x761B45794B10407DLL;
	*(long long *)&cipher[16] = 0x6E005B71491F585FLL;
	*(long long *)&cipher[24] = 0x45045205575D01LL;
	int key = 26;
	for (int i = 0; i < 32; i++)
		cipher[i] ^= key++;
	printf("%s\n", cipher);
	return 0;
}