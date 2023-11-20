#include <cstdio>
#include <cstdint>

void decrypt(uint32_t* v, uint32_t* key)
{
	uint32_t v0 = v[0], v1 = v[1];
	uint32_t delta = 0x11451411;
	uint32_t sum = delta * 32;

	for (int i = 0; i < 32; i++)
	{
		v1 -= (((v0 << 4) ^ (v0 >> 5)) + v0) ^ (sum + key[(sum >> 11) & 3]);
		sum -= delta;
		v0 -= (((v1 << 4) ^ (v1 >> 5)) + v1) ^ (sum + key[sum & 3]);
	}

	v[0] = v0;
	v[1] = v1;
	return ;
}

int main()
{
	uint32_t key[4];
	key[0] = 429459223;
	key[1] = 537200643;
	key[2] = 537462290;
	key[3] = 537006083;

	uint32_t enc[12];
	enc[0] = 0xC474145E;
	enc[1] = 0x39D42171;
	enc[2] = 0xF527A9EB;
	enc[3] = 0xE32AB90A;
	enc[4] = 0x3F5BD7F7;
	enc[5] = 0xD673678C;

	for (int i = 4; i >= 0; i--)
		decrypt(&enc[i], key);
	for (int i = 0; i <= 5; i++)
	{
		printf("%c", enc[i] & 0xFF);
		printf("%c", (enc[i] & 0xFF00) >> 8);
		printf("%c", (enc[i] & 0xFF0000) >> 16);
		printf("%c", (enc[i] & 0xFF000000) >> 24);
	}
	putchar('\n');
	return 0;
}