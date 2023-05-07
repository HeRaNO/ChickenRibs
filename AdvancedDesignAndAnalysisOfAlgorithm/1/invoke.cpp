#include <ctime>
#include <cstdio>
#include <cstdlib>

int main()
{
	// prepare
	system("g++ gen.cpp -o gen -O2 -std=c++17");
	system("g++ checker.cpp -o checker -O2 -std=c++17");
	system("g++ naive.cpp -o naive -O2 -std=c++17 -Wl,--stack=1000000000");
	system("g++ graham.cpp -o graham -O2 -std=c++17 -Wl,--stack=1000000000");
	system("g++ dc.cpp -o dc -O2 -std=c++17 -Wl,--stack=1000000000");

	clock_t st, ed;

	for (int n = 10; n <= 100; n += 10)
	{
		char gen_cmd[100];
		sprintf(gen_cmd, "gen %d > input", n);
		system(gen_cmd);

		printf("n = %d\n", n);

		st = clock();
		system("naive < input > naive_out");
		ed = clock();
		printf("naive time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("graham < input > graham_out");
		ed = clock();
		printf("graham time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("dc < input > dc_out");
		ed = clock();
		printf("dc time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		int ret = system("checker input naive_out graham_out");
		if (ret)
			puts("Wrong answer");
		ret = system("checker input graham_out dc_out");
		if (ret)
			puts("Wrong answer");
	}

	for (int n = 100; n <= 1000; n += 100)
	{
		char gen_cmd[100];
		sprintf(gen_cmd, "gen %d > input", n);
		system(gen_cmd);

		printf("n = %d\n", n);

		st = clock();
		system("naive < input > naive_out");
		ed = clock();
		printf("naive time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("graham < input > graham_out");
		ed = clock();
		printf("graham time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("dc < input > dc_out");
		ed = clock();
		printf("dc time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		int ret = system("checker input naive_out graham_out");
		if (ret)
			puts("Wrong answer");
		ret = system("checker input graham_out dc_out");
		if (ret)
			puts("Wrong answer");
	}

	for (int n = 1000; n <= 10000; n += 1000)
	{
		char gen_cmd[100];
		sprintf(gen_cmd, "gen %d > input", n);
		system(gen_cmd);

		printf("n = %d\n", n);

		st = clock();
		system("naive < input > naive_out");
		ed = clock();
		printf("naive time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("graham < input > graham_out");
		ed = clock();
		printf("graham time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("dc < input > dc_out");
		ed = clock();
		printf("dc time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		int ret = system("checker input naive_out graham_out");
		if (ret)
			puts("Wrong answer");
		ret = system("checker input graham_out dc_out");
		if (ret)
			puts("Wrong answer");
	}

	for (int n = 10000; n <= 100000; n += 10000)
	{
		char gen_cmd[100];
		sprintf(gen_cmd, "gen %d > input", n);
		system(gen_cmd);

		printf("n = %d\n", n);

		st = clock();
		system("graham < input > graham_out");
		ed = clock();
		printf("graham time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);

		st = clock();
		system("dc < input > dc_out");
		ed = clock();
		printf("dc time used: %lfs\n", (double)(ed - st) / CLOCKS_PER_SEC);
	}
	return 0;
}