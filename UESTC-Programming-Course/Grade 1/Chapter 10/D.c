#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int hand[5][2];

void SelectionSort(int n)
{
	if (!n) return ;
	int i;
	for (i=0;i<n-1;i++)
		if (hand[i][0]>hand[n-1][0]||
			(hand[i][0]==hand[n-1][0]&&hand[i][1]>hand[n-1][1]))
		{
			int t=hand[i][0];hand[i][0]=hand[n-1][0];hand[n-1][0]=t;
			t=hand[i][1];hand[i][1]=hand[n-1][1];hand[n-1][1]=t;
		}
	SelectionSort(n-1);
	return ;
}

void readCards()
{
	int i,tx=-1,ty=-1,valid=0;char s[1000];
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
		for (i=0;i<valid&&!bad;i++)
			if (hand[i][0]==tx&&hand[i][1]==ty) bad=true;
		if (bad)
		{
			puts("Duplicate card; ignored.");
			continue;
		}
		hand[valid][0]=tx;hand[valid][1]=ty;valid++;
	}
	SelectionSort(5);
	return ;
}

bool isStraightFlush()
{
	int i;
	for (i=1;i<5;i++) if (hand[i][0]!=hand[i-1][0]+1) return false;
	for (i=1;i<5;i++) if (hand[i][1]!=hand[i-1][1])   return false;
	return true;
}

bool isFourSame()
{
	int i;
	if (hand[0][0]==hand[1][0]&&
		hand[1][0]==hand[2][0]&&
		hand[2][0]==hand[3][0]) return true;
	if (hand[4][0]==hand[3][0]&&
		hand[1][0]==hand[2][0]&&
		hand[2][0]==hand[3][0]) return true;
	return false;
}

bool isFullHouse()
{
	int i,typ[4]={0};bool f=false;
	for (i=0;i<5;i++) ++typ[hand[i][1]];
	for (i=0;i<4&&!f;i++) if (typ[i]==3) f=true;
	if (!f) return false;
	for (i=0;i<4&&f;i++) if (typ[i]==2) f=false;
	if (f) return false;
	return true;
}

bool isFulsh()
{
	int i;
	for (i=1;i<5;i++) if (hand[i][1]!=hand[i-1][1]) return false;
	return true;
}

bool isStraight()
{
	int i;
	for (i=1;i<5;i++) if (hand[i][0]!=hand[i-1][0]+1) return false;
	return true;
}

bool isThreeSame()
{
	int i;
	if (hand[0][0]==hand[1][0]&&hand[1][0]==hand[2][0]) return true;
	if (hand[3][0]==hand[1][0]&&hand[1][0]==hand[2][0]) return true;
	if (hand[4][0]==hand[3][0]&&hand[3][0]==hand[2][0]) return true;
	return false;
}

bool isTwoPair()
{
	int i,cnt=0;
	for (i=1;i<5;i++) if (hand[i][0]==hand[i-1][0]) ++cnt;
	return cnt==2;
}

bool isPair()
{
	int i,cnt=0;
	for (i=1;i<5;i++) if (hand[i][0]==hand[i-1][0]) ++cnt;
	return cnt==1;
}

void analyzeCards()
{
	if (isStraightFlush()){puts("Straight flush\n");return ;}
	if (isFourSame()){puts("Four of a kind\n");return ;}
	if (isFullHouse()){puts("Full house\n");return ;}
	if (isFulsh()){puts("Fulsh\n");return ;}
	if (isStraight()){puts("Straight\n");return ;}
	if (isThreeSame()){puts("Three of a kind\n");return ;}
	if (isTwoPair()){puts("Two pairs\n");return ;}
	if (isPair()){puts("Pair\n");return ;}
	puts("High card\n");return ;
}

int main()
{
	while (true){readCards();analyzeCards();}
	return 0;
}
