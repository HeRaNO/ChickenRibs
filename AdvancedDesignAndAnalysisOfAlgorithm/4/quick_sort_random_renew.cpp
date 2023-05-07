#include <tuple>
#include <cstdio>
#include <random>
#include <vector>
#include <utility>

std::random_device rd;
std::mt19937 rng(rd());

std::pair<int, int> RandomPartition(std::vector<int> &a, int p, int r)
{
	std::uniform_int_distribution<int> dist(p, r);
	int x = a[dist(rng)];
	int i = p, j = p, k = r;
	while (i <= k)
	{
		if (a[i] < x) std::swap(a[i++], a[j++]);
		else if (x < a[i]) std::swap(a[i], a[k--]);
		else ++i;
	}
	return {j, k};
}

void InsertionSort(std::vector<int> &a, int p, int r)
{
	for (int i = p + 1; i <= r; i++)
	{
		int k = a[i]; int j;
		for (j = i - 1; j >= p && a[j] > k; j--)
			a[j + 1] = a[j];
		a[j + 1] = k;
	}
	return ;
}

void QuickSort(std::vector<int> &a, int p, int r)
{
	if (p >= r) return ;
	if (r - p < 16)
	{
		InsertionSort(a, p, r);
		return ;
	}
	int j, k;
	std::tie(j, k) = RandomPartition(a, p, r);
	QuickSort(a, p, j - 1);
	QuickSort(a, k, r);
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