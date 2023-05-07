#include "testlib.h"

int main(int argc, char *argv[])
{
	registerGen(argc, argv, 1);
	int n = opt<int>(1);
	printf("%d\n", n);
	std::set<std::pair<int, int>> S;
	while (S.size() != n) S.insert({rnd.next(0, 10000), rnd.next(0, 10000)});
	std::vector<std::pair<int, int>> v;
	for (std::pair<int, int> p : S) v.push_back(p);
	shuffle(v.begin(), v.end());
	for (auto [x, y] : v) printf("%d %d\n", x, y);
	return 0;
}