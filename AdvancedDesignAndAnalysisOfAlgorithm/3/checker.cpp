#include "testlib.h"

int readAndCheck(InStream &in, int n, int x)
{
	std::vector<bool> U(x, false);
	int m = in.readInt(); in.nextLine();
	for (int i = 1; i <= m; i++)
	{
		std::vector<std::string> Cs = split(trim(in.readLine()), ' ');
		for (std::string cs : Cs)
		{
			long long i = stringToLongLong(in, cs.c_str());
			if (!(i >= 1 && i <= x))
				in.quitf(_wa, "wrong number: %s", cs.c_str());
			U[(int)i - 1] = true;
		}
	}
	for (int i = 0; i < x; i++)
		if (!U[i]) in.quitf(_wa, "%d is not covered", i + 1);
	return m;
}

int main(int argc, char *argv[])
{
	registerTestlibCmd(argc, argv);
	int n = inf.readInt(), x = inf.readInt();
	int jans = readAndCheck(ans, n, x);
	int pans = readAndCheck(ouf, n, x);
	quitf(_ok, "ok, greedy: %d, LP: %d", jans, pans);
	return 0;
}