#include <stdio.h>

typedef struct 
{
	char *contury;
	int code;
}dailing_code;

const dailing_code a[]={
	{"Argentina",54},{"Bangladesh",880},
	{"Brazil",55},{"Burma (Myanmar)",95},
	{"China",86},{"Colombia",57},
	{"Congo, Dem. Rep. of",243},{"Egypt",20},
	{"Ethiopia",251},{"France",33},
	{"Germany",49},{"India",91},
	{"Indonesia",62},{"Iran",98},
	{"Italy",39},{"Japan",81},
	{"Mexico",52},{"Nigeria",234},
	{"Pakistan",92},{"Philippines",63},
	{"Poland",48},{"Russia",7},
	{"South Africa",27},{"Korea",82},
	{"Spain",34},{"Sudan",249},
	{"Thailand",66},{"Turkey",90},
	{"Ukraine",380},{"United Kingdom",44},
	{"United States",1},{"Vietnam",84}
};

int main()
{
	int n,i;
	puts("Enter dialing code:");
	scanf("%d",&n);
	for (i=0;i<32;i++)
		if (a[i].code==n)
		{
			printf("The country with dialing code %d is %s\n",n,a[i].contury);
			return 0;
		}
	puts("No corresponding country found");
	return 0;
}
