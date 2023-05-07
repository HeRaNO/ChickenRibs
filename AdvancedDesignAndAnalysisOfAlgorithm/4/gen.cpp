#include "testlib.h"

const int N = 1'000'000'000;

int main(int argc, char *argv[])
{
	registerGen(argc, argv, 1);
	int n = opt<int>(1), k = opt<int>(2);
	int sz = k * 100'000;

	std::vector<int> a = rnd.distinct(n - sz, -N, N - 1);
	for (; sz; sz--) a.push_back(N);
	shuffle(a.begin(), a.end());

	printf("%d\n", n);
	for (int i = 0; i < n; i++)
		printf("%d%c", a[i], " \n"[i == n - 1]);
	return 0;
}