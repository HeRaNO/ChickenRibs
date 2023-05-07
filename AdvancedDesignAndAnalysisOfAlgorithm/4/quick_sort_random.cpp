#include <cstdio>
#include <random>
#include <vector>

std::random_device rd;
std::mt19937 rng(rd());

int RandomPartition(std::vector<int> &a, int p, int r)
{
	std::uniform_int_distribution<int> dist(p, r);
	int i = dist(rng);
	std::swap(a[r], a[i]);
	int x = a[r]; i = p - 1;
	for (int j = p; j < r; j++)
		if (a[j] <= x)
			std::swap(a[++i], a[j]);
	std::swap(a[++i], a[r]);
	return i;
}

void QuickSort(std::vector<int> &a, int p, int r)
{
	if (p >= r) return ;
	int q = RandomPartition(a, p, r);
	QuickSort(a, p, q - 1);
	QuickSort(a, q + 1, r);
	return ;
}

int main()
{
	int n; scanf("%d", &n);
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	QuickSort(a, 0, n - 1);
	for (int i = 0; i < n; i++)
		printf("%d%c", a[i], " \n"[i == n - 1]);
	return 0;
}