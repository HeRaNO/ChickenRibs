#include <ctime>
#include <cstdio>
#include <cstdlib>

int main()
{
	// prepare
	system("g++ gen.cpp -o gen -O2 -std=c++17");
	system("g++ checker.cpp -o checker -O2 -std=c++17");

	int ret;
	clock_t st, ed;

	system("gen 100 100 > input");
	printf("|X| = |F| = 100\n");

	st = clock();
	system("python greedy.py < input > greedy_out");
	ed = clock();
	printf("greedy time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

	st = clock();
	system("python lp.py < input > lp_out");
	ed = clock();
	printf("lp time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

	ret = system("checker input lp_out greedy_out");
	if (ret)
		puts("Wrong answer");

	system("gen 1000 1000 > input");
	printf("|X| = |F| = 1000\n");

	st = clock();
	system("python greedy.py < input > greedy_out");
	ed = clock();
	printf("greedy time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

	st = clock();
	system("python lp.py < input > lp_out");
	ed = clock();
	printf("lp time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

	ret = system("checker input lp_out greedy_out");
	if (ret)
		puts("Wrong answer");

	system("gen 5000 5000 > input");
	printf("|X| = |F| = 5000\n");

	st = clock();
	system("python greedy.py < input > greedy_out");
	ed = clock();
	printf("greedy time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

	st = clock();
	system("python lp.py < input > lp_out");
	ed = clock();
	printf("lp time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

	ret = system("checker input lp_out greedy_out");
	if (ret)
		puts("Wrong answer");
	return 0;
}