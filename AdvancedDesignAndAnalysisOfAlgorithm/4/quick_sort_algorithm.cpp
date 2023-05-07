#include <cstdio>
#include <vector>
#include <algorithm>

int main()
{
	int n; scanf("%d", &n);
	std::vector<int> a(n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	std::sort(a.begin(), a.end());
	for (int i = 0; i < n; i++)
		printf("%d%c", a[i], " \n"[i == n - 1]);
	return 0;
}