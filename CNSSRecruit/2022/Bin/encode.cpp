#include <cstdio>
#include <string>

char convert[128];
const char EncodeTable[] = "abcd4EFGHij8k0lMNOPqr6stU91VWXyz7+/ABCDefg2hI5JKLmnopQRST3uvwxYZ";

std::string makeString(long long x)
{
	std::string res = "";
	for (; x; x >>= 8)
		res.push_back(x & 127);
	return res;
}

int main()
{
	std::string x = makeString(4986983797375586901LL);
	std::string y = makeString(7091289747300042544LL);
	std::string z = makeString(8666442117137191511LL);
	x += y; x += z;
	for (int i = 0; i < 63; i++)
		convert[EncodeTable[i]] = i;
	for (int i = 0; i < x.length(); i += 4)
	{
		char x0 = (convert[x[i + 0]] << 2) | (convert[x[i + 1]] >> 4);
		char x1 = ((convert[x[i + 1]] & 15) << 4) | (convert[x[i + 2]] >> 2);
		char x2 = ((convert[x[i + 2]] & 3) << 6) | convert[x[i + 3]];
		printf("%c%c%c", x0, x1, x2);
	}
	puts("");
	return 0;
}
