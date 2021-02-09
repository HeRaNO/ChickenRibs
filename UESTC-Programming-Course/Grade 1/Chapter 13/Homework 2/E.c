#include <stdio.h>
#include <string.h>

char mx[20],mn[20],s[20];

int main()
{
	scanf("%s",s);
	printf("Enter word:\n");
	strcpy(mx,s);strcpy(mn,s);
	while (1)
	{
		if (!~scanf("%s",s)) break;
		printf("Enter word:\n");
		if (strcmp(mx,s)<0) strcpy(mx,s);
		if (strcmp(mn,s)>0) strcpy(mn,s);
		if (strlen(s)==4) break;
	}
	printf("\nSmallest word: %s\n",mn);
	printf("Largest word: %s\n",mx);
	return 0;
}
