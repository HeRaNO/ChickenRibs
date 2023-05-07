#include "testlib.h"

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	int jans = ans.readInt();
	int pans = ouf.readInt();
	if (jans != pans)
		quitf(_wa, "wrong convex hull size");
	std::vector<std::pair<int, int>> jch, pch;
	for (int i = 1; i <= pans; i++)
	{
		int x = ans.readInt(), y = ans.readInt();
		jch.push_back({x, y});
	}
	for (int i = 1; i <= pans; i++)
	{
		int x = ouf.readInt(), y = ouf.readInt();
		pch.push_back({x, y});
	}
	std::sort(jch.begin(), jch.end());
	std::sort(pch.begin(), pch.end());
	if (jch != pch)
		quitf(_wa, "wrong convex hull");
	quitf(_ok, "ok");
	return 0;
}