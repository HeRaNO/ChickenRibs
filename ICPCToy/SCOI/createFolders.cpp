#include <cassert>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

inline int getArg(const char* nowArg, const char* arg)
{
	int x = atoi(arg);
	if (!x)
	{
		fprintf(stderr, "Error: %s error\n", nowArg);
		exit(0);
	}
	return x;
}

int main(int argc, char const *argv[])
{
	if (argc != 4)
	{
		fprintf(stderr, "Create folders for contestants here\n");
		fprintf(stderr, "Usage: %s <digit> <first> <last>\n", argv[0]);
		fprintf(stderr, "digit: the number of digits in ID (exclude \'SC-\')\n");
		fprintf(stderr, "first: the first ID of this room\n");
		fprintf(stderr, "last: the last ID of this room\n");
		return 0;
	}

	int digit = getArg("<digit>", argv[1]);
	int first = getArg("<first>", argv[2]);
	int last = getArg("<last>", argv[3]);
	assert(first <= last);
	int sucCnt = 0;

	for (int i = first; i <= last; i++)
	{
		std::stringstream ss;
		ss << std::setw(digit) << std::setfill('0') << i;
		std::string fName;
		ss >> fName;
		fName = "SC-" + fName;
		if (!fs::is_directory(fName))
		{
			fs::create_directory(fName);
			++sucCnt;
		}
	}

	fprintf(stderr, "Create folders finished: %d / %d (success / all)\n", sucCnt, last - first + 1);
	return 0;
}