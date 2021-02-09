#include <stdio.h>
#include <string.h>

const char Week[7][10]={
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday",
	"Friday",
	"Saturday",
	"Sunday"
};

int main(int argc, char const *argv[])
{
	int i;
	for (i=0;i<7;i++)
		if (strcmp(argv[1],Week[i])==0)
		{
			printf("%s is %d.\n",argv[1],i+1);
			return 0;
		}
	puts("Not found!");
	return 0;
}
