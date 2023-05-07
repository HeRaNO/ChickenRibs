#include "testlib.h"
#include <numeric>

int main(int argc, char *argv[])
{
	registerGen(argc, argv, 1);
	int n = opt<int>(1), x = opt<int>(2);
	std::vector<std::vector<int>> F;

	std::vector<int> U(x);
	std::iota(U.begin(), U.end(), 1);
	shuffle(U.begin(), U.end());
	std::vector<int> L = rnd.partition(rnd.next(n / 5 - 5, n / 5 + 5), x, 1);
	int l = 0;
	for (int n : L)
	{
		int r = l + n;
		std::vector<int> S;
		for (int i = l; i < r; i++) S.push_back(U[i]);
		int C = rnd.next(0, 5);
		while (C--)
		{
			int t; bool f = false;
			while (!f)
			{
				f = true; t = rnd.next(1, x);
				for (int i : S)
					if (t == i)
					{
						f = false; break;
					}
			}
			S.push_back(t);
		}
		F.push_back(S); l += n;
	}
	while (F.size() < n)
	{
		int C = rnd.next(1, x / 2);
		std::vector<int> v = rnd.distinct(C, 1, x);
		shuffle(v.begin(), v.end());
		F.push_back(v);
	}
	shuffle(F.begin(), F.end());
	ensure(F.size() == n);

	printf("%d %d\n", n, x);
	for (auto S : F)
		for (int i = 0; i < S.size(); i++)
			printf("%d%c", S[i], " \n"[i + 1 == S.size()]);
	return 0;
}