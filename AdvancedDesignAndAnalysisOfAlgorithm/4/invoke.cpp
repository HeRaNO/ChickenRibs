#include <ctime>
#include <cstdio>
#include <cstdlib>

int main()
{
	// prepare
	system("g++ gen.cpp -o gen -O2 -std=c++17");
	system("g++ lcmp.cpp -o lcmp -O2 -std=c++17");
	system("g++ quick_sort_algorithm.cpp -o quick_sort_algorithm -O2 -std=c++17 -Wl,--stack=1000000000");
	system("g++ quick_sort_random.cpp -o quick_sort_random -O2 -std=c++17 -Wl,--stack=1000000000");
	system("g++ quick_sort_random_renew.cpp -o quick_sort_random_renew -O2 -std=c++17 -Wl,--stack=1000000000");

	clock_t st, ed;

	for (int k = 0; k <= 5; k++)
	{
		char gen_cmd[100];
		sprintf(gen_cmd, "gen 1000000 %d > input", k);
		system(gen_cmd);

		printf("k = %d\n", k);

		st = clock();
		system("quick_sort_random < input > quick_sort_random_out");
		ed = clock();
		printf("quick_sort_random time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("quick_sort_random_renew < input > quick_sort_random_renew_out");
		ed = clock();
		printf("quick_sort_random_renew time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("quick_sort_algorithm < input > quick_sort_algorithm_out");
		ed = clock();
		printf("quick_sort_algorithm time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		int ret = system("lcmp input quick_sort_random_out quick_sort_algorithm_out");
		if (ret)
			puts("Wrong answer");
		ret = system("lcmp input quick_sort_random_out quick_sort_random_renew_out");
		if (ret)
		{
			puts("Wrong answer");
			break;
		}
	}
	for (int k = 6; k <= 10; k++)
	{
		char gen_cmd[100];
		sprintf(gen_cmd, "gen 1000000 %d > input", k);
		system(gen_cmd);

		printf("k = %d\n", k);

		st = clock();
		system("quick_sort_random_renew < input > quick_sort_random_renew_out");
		ed = clock();
		printf("quick_sort_random_renew time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("quick_sort_algorithm < input > quick_sort_algorithm_out");
		ed = clock();
		printf("quick_sort_algorithm time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		int ret = system("lcmp input quick_sort_algorithm_out quick_sort_random_renew_out");
		if (ret)
		{
			puts("Wrong answer");
			break;
		}
	}
	return 0;
}