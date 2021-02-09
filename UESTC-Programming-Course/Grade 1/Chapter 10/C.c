#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void readCards(int exist[][4],int num[],int typ[])
{
	int i,j;
	for (i=0;i<13;i++) typ[i]=0;
	for (i=0;i<13;i++)
	{
		num[i]=0;
		for (j=0;j<4;j++) exist[i][j]=0;
	}
	int tx=-1,ty=-1,valid=0;char s[1000];
	while (valid<5)
	{
		bool bad=false;
		puts("Enter a card: ");
		scanf("%s",s);
		switch (s[0])
		{
			case '0':exit(0);
			case '2':tx=0;break;
			case '3':tx=1;break;
			case '4':tx=2;break;
			case '5':tx=3;break;
			case '6':tx=4;break;
			case '7':tx=5;break;
			case '8':tx=6;break;
			case '9':tx=7;break;
			case 't':case 'T':tx=8;break;
			case 'j':case 'J':tx=9;break;
			case 'q':case 'Q':tx=10;break;
			case 'k':case 'K':tx=11;break;
			case 'a':case 'A':tx=12;break;
			default:bad=true;
		}
		switch (s[1])
		{
			case 'c':case 'C':ty=0;break;
			case 'd':case 'D':ty=1;break;
			case 'h':case 'H':ty=2;break;
			case 's':case 'S':ty=3;break;
			default:bad=true;
		}
		if (strlen(s)!=2) bad=true;
		if (bad)
		{
			puts("Bad card; ignored.");
			continue;
		}
		if (exist[tx][ty])
		{
			puts("Duplicate card; ignored.");
			continue;
		}
		valid++;++num[tx];++typ[ty];exist[tx][ty]=true;
	}
	return ;
}

bool isStraightFlush(int num[],int typ[])
{
	if (typ[0]==5||typ[1]==5||typ[2]==5||typ[3]==5)
	{
		int i;
		for (i=0;i<=8;i++)
		{
			bool f=true;int j;
			for (j=0;j<5&&f;j++) if (!num[i+j]) f=false;
			if (f) return true;
		}
	}
	return false;
}

bool isFourSame(int typ[])
{
	int i;
	for (i=0;i<13;i++) if (typ[i]==4) return true;
	return false;
}

bool isFullHouse(int typ[])
{
	int i;bool f=false;
	for (i=0;i<4&&!f;i++) if (typ[i]==3) f=true;
	if (!f) return false;
	for (i=0;i<4&&f;i++) if (typ[i]==2) f=false;
	if (f) return false;
	return true;
}

bool isFulsh(int typ[])
{
	if (typ[0]==5||typ[1]==5||typ[2]==5||typ[3]==5) return true;
	return false;
}

bool isStraight(int num[])
{
	int i;
	for (i=0;i<=8;i++)
	{
		bool f=true;int j;
		for (j=0;j<5&&f;j++) if (!num[i+j]) f=false;
		if (f) return true;
	}
	return false;
}

bool isThreeSame(int num[])
{
	int i;
	for (i=0;i<13;i++) if (num[i]==3) return true;
	return false;
}

bool isTwoPair(int num[])
{
	int i,cnt=0;
	for (i=0;i<13;i++) if (num[i]==2) ++cnt;
	return cnt==2;
}

bool isPair(int num[])
{
	int i,cnt=0;
	for (i=0;i<13;i++) if (num[i]==2) ++cnt;
	return cnt==1;
}

void analyzeCards(int num[],int typ[])
{
	if (isStraightFlush(num,typ)){puts("Straight flush\n");return ;}
	if (isFourSame(num)){puts("Four of a kind\n");return ;}
	if (isFullHouse(typ)){puts("Full house\n");return ;}
	if (isFulsh(typ)){puts("Fulsh\n");return ;}
	if (isStraight(num)){puts("Straight\n");return ;}
	if (isThreeSame(num)){puts("Tree of a kind\n");return ;}
	if (isTwoPair(num)){puts("Two pairs\n");return ;}
	if (isPair(num)){puts("Pair\n");return ;}
	puts("High card\n");return ;
}

int main()
{
	int exist[13][4],num[13],typ[4];
	while (true){readCards(exist,num,typ);analyzeCards(num,typ);}
	return 0;
}
