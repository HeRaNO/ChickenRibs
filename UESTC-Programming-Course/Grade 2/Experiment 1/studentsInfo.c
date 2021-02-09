#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30

typedef struct {
	char sNo[MAX_ID_LEN];
	char sName[MAX_NAME_LEN];
	bool sex; /* 0 - 男    1 - 女 */
	bool major; /* 0 - 软件技术    1 - 人工智能 */
} Student;

typedef struct {
	char cNo[MAX_ID_LEN];
	char cName[MAX_NAME_LEN];
	int classHours;
} Course;

typedef struct {
	char sNo[MAX_ID_LEN];
	char cNo[MAX_NAME_LEN];
	int score;
} Grade;

typedef struct {
	Student a;
	Course b;
	int score;
} Report;

typedef struct snode {
	Student info;
	struct snode *nxt;
} studentList;

typedef struct cnode {
	Course info;
	struct cnode *nxt;
} courseList;

typedef struct gnode {
	Grade info;
	struct gnode *nxt;
} gradeList;

typedef struct rnode {
	Report info;
	struct rnode *nxt;
} reportList;

studentList *slist = NULL, *slist_last = NULL;
courseList *clist = NULL, *clist_last = NULL;
gradeList *glist = NULL, *glist_last = NULL;
reportList *rlist = NULL, *rlist_last = NULL;

void outputMenu()
{
	puts("*******************************************");
	puts("1. 输入学生信息并保存；");
	puts("2. 输入课程信息并保存；");
	puts("3. 输入成绩信息并保存；");
	puts("4. 读取学生信息，创建按学号升序的单向链表；");
	puts("5. 读取课程信息，创建按课程号升序的单向链表；");
	puts("6. 读取成绩信息，创建按学号和课程号升序的单向链表；");
	puts("7. 读取成绩信息，查询所有学生所有课程的考试成绩（需先运行 1, 2, 3）；");
	puts("8. 读取成绩信息，查询所有学生指定课程的考试成绩（需先运行 7）；");
	puts("9. 读取成绩信息，查询指定课程成绩小于 60 分的学生（需先运行 7）；");
	puts("a. 将 4 中生成的链表反转（需先运行 4）；");
	puts("b. 用链式队列解决 7 的问题；");
	puts("其他. 退出系统；");
	puts("*******************************************");
	return ;
}

void inputStudentInfo()
{
	FILE *fp = fopen("student.dat", "w");
	char t[200]; int i;
	for (i = 1; i <= 10; i++)
	{
		printf("请输入学号：");
		scanf("%s", t); fprintf(fp, "%s", t);
		printf("请输入姓名：");
		scanf("%s", t); fprintf(fp, " %s", t);
		printf("请输入性别（F - 女，M - 男）：");
		scanf("%s", t); fprintf(fp, " %s", t);
		printf("请输入专业（S - 软件技术，A - 人工智能）：");
		scanf("%s", t); fprintf(fp, " %s\n", t);
		puts("录入成功");
	}
	fclose(fp);
	puts("操作成功");
	return ;
}

void inputCourseInfo()
{
	FILE *fp = fopen("course.dat", "w");
	char t[200]; int h, i;
	for (i = 1; i <= 3; i++)
	{
		printf("请输入课程编号：");
		scanf("%s", t); fprintf(fp, "%s", t);
		printf("请输入课程名称：");
		scanf("%s", t); fprintf(fp, " %s", t);
		printf("请输入课时数：");
		scanf("%d", &h); fprintf(fp, " %d\n", h);
		puts("录入成功");
	}
	fclose(fp);
	puts("操作成功");
	return ;
}

void inputGradeInfo()
{
	FILE *fp = fopen("courseGrade.dat", "w");
	char t[200]; int h, i;
	for (i = 1; i <= 30; i++)
	{
		printf("请输入学号：");
		scanf("%s", t); fprintf(fp, "%s", t);
		printf("请输入课程号：");
		scanf("%s", t); fprintf(fp, " %s", t);
		printf("请输入考试成绩：");
		scanf("%d", &h); fprintf(fp, " %d\n", h);
		puts("录入成功");
	}
	fclose(fp);
	puts("操作成功");
	return ;
}

void rwGenerateStudentLink()
{
	FILE *fp = fopen("student.dat", "r");

	if (fp == NULL)
	{
		puts("文件打开失败");
		return ;
	}

	char t[3]; int i;

	slist = NULL; slist_last = NULL;
	for (i = 1; i <= 10; i++)
	{
		studentList *a = (studentList *)malloc(sizeof(studentList));
		a -> nxt = NULL;
		fscanf(fp, "%s", (a -> info).sNo);
		fscanf(fp, "%s", (a -> info).sName);
		fscanf(fp, "%s", t);
		if (t[0] == 'F') (a -> info).sex = true;
		else (a -> info).sex = false;
		fscanf(fp, "%s", t);
		if (t[0] == 'A') (a -> info).major = true;
		else (a -> info).major = false;

		if (slist == NULL)
		{
			slist = a;
			slist_last = a;
		}
		else
		{
			studentList *p = slist, *pre = NULL;
			while (p)
			{
				if (strcmp(p -> info.sNo, a -> info.sNo) > 0)
					break;
				pre = p;
				p = p -> nxt;
			}
			if (!pre)
			{
				a -> nxt = slist;
				slist = a;
			}
			else if (pre == slist_last)
			{
				slist_last -> nxt = a;
				slist_last = a;
			}
			else
			{
				pre -> nxt = a;
				a -> nxt = p;
			}
		}
	}
	puts("操作成功");
	studentList *p = slist;
	while (p)
	{
		#define aa p -> info
		printf("%s %s %s %s\n", aa.sNo, aa.sName, aa.sex ? "F" : "M", aa.major ? "A" : "S");
		#undef aa
		p = p -> nxt;
	}

	fclose(fp);
	return ;
}

void rwGenerateCourseLink()
{
	FILE *fp = fopen("course.dat", "r");

	if (fp == NULL)
	{
		puts("文件打开失败");
		return ;
	}

	int t, i;

	clist = NULL; clist_last = NULL;
	for (i = 1; i <= 3; i++)
	{
		courseList *a = (courseList *)malloc(sizeof(courseList));
		a -> nxt = NULL;
		fscanf(fp, "%s", (a -> info).cNo);
		fscanf(fp, "%s", (a -> info).cName);
		fscanf(fp, "%d", &(a -> info).classHours);

		if (clist == NULL)
		{
			clist = a;
			clist_last = a;
		}
		else
		{
			courseList *p = clist, *pre = NULL;
			while (p)
			{
				if (strcmp(p -> info.cNo, a -> info.cNo) > 0)
					break;
				pre = p;
				p = p -> nxt;
			}
			if (!pre)
			{
				a -> nxt = clist;
				clist = a;
			}
			else if (pre == clist_last)
			{
				clist_last -> nxt = a;
				clist_last = a;
			}
			else
			{
				pre -> nxt = a;
				a -> nxt = p;
			}
		}
	}
	puts("操作成功");
	courseList *p = clist;
	while (p)
	{
		#define aa p -> info
		printf("%s %s %d\n", aa.cNo, aa.cName, aa.classHours);
		#undef aa
		p = p -> nxt;
	}

	fclose(fp);
	return ;
}

void rwGenerateGradeLink()
{
	FILE *fp = fopen("courseGrade.dat", "r");

	if (fp == NULL)
	{
		puts("文件打开失败");
		return ;
	}

	int t, i;

	glist = NULL; glist_last = NULL;
	for (i = 1; i <= 30; i++)
	{
		gradeList *a = (gradeList *)malloc(sizeof(gradeList));
		a -> nxt = NULL;
		fscanf(fp, "%s", (a -> info).sNo);
		fscanf(fp, "%s", (a -> info).cNo);
		fscanf(fp, "%d", &(a -> info).score);

		if (glist == NULL)
		{
			glist = a;
			glist_last = a;
		}
		else
		{
			gradeList *p = glist, *pre = NULL;
			while (p)
			{
				int tmp = strcmp(p -> info.cNo, a -> info.cNo);
				if (tmp > 0 || (!tmp && p -> info.score < a -> info.score))
					break;
				pre = p;
				p = p -> nxt;
			}
			if (!pre)
			{
				a -> nxt = glist;
				glist = a;
			}
			else if (pre == glist_last)
			{
				glist_last -> nxt = a;
				glist_last = a;
			}
			else
			{
				pre -> nxt = a;
				a -> nxt = p;
			}
		}
	}
	puts("操作成功");
	gradeList *p = glist;
	while (p)
	{
		#define aa p -> info
		printf("%s %s %d\n", aa.cNo, aa.sNo, aa.score);
		#undef aa
		p = p -> nxt;
	}

	fclose(fp);
	return ;
}

void generateReportLink()
{
	FILE *fp = fopen("courseGrade.dat", "r");
	FILE *fs = fopen("studentGrade.dat", "w");

	if (fp == NULL || fs == NULL)
	{
		puts("文件打开失败");
		return ;
	}
	int t, i;

	rlist = NULL; rlist_last = NULL;
	for (i = 1; i <= 30; i++)
	{
		reportList *a = (reportList *)malloc(sizeof(reportList));
		a -> nxt = NULL;
		fscanf(fp, "%s", (a -> info.a).sNo);
		fscanf(fp, "%s", (a -> info.b).cNo);
		fscanf(fp, "%d", &(a -> info.score));

		studentList *b = slist;
		while (b)
		{
			if (strcmp(b -> info.sNo, (a -> info.a).sNo) == 0)
				break;
			b = b -> nxt;
		}

		memcpy((a -> info.a).sName, b -> info.sName, sizeof(b -> info.sName));
		(a -> info.a).sex = b -> info.sex;
		(a -> info.a).major = b -> info.major;

		courseList *c = clist;
		while (c)
		{
			if (strcmp(c -> info.cNo, (a -> info.b).cNo) == 0)
				break;
			c = c -> nxt;
		}

		memcpy((a -> info.b).cName, c -> info.cName, sizeof(c -> info.cName));
		a -> info.b.classHours = c -> info.classHours;

		if (rlist == NULL)
		{
			rlist = a;
			rlist_last = a;
		}
		else
		{
			reportList *p = rlist, *pre = NULL;
			while (p)
			{
				int tmp = strcmp(p -> info.b.cNo, a -> info.b.cNo);
				if (tmp > 0 || (!tmp && p -> info.score < a -> info.score))
					break;
				pre = p;
				p = p -> nxt;
			}
			if (!pre)
			{
				a -> nxt = rlist;
				rlist = a;
			}
			else if (pre == rlist_last)
			{
				rlist_last -> nxt = a;
				rlist_last = a;
			}
			else
			{
				pre -> nxt = a;
				a -> nxt = p;
			}
		}
	}
	puts("操作成功");
	reportList *p = rlist;
	while (p)
	{
		#define aa p -> info.a
		printf("%s %s %s %s ", aa.sNo, aa.sName, aa.sex ? "F" : "M", aa.major ? "A" : "S");
		fprintf(fs, "%s %s %s %s ", aa.sNo, aa.sName, aa.sex ? "F" : "M", aa.major ? "A" : "S");
		#undef aa
		#define aa p -> info.b
		printf("%s %s %d %d\n", aa.cNo, aa.cName, aa.classHours, p -> info.score);
		fprintf(fs, "%s %s %d %d\n", aa.cNo, aa.cName, aa.classHours, p -> info.score);
		#undef aa
		p = p -> nxt;
	}

	fclose(fp);
	return ;
}

void generatePartReportLink()
{
	printf("请输入查询的课程号：");
	char t[10];
	scanf("%s", t);
	reportList *p = rlist;
	bool haveCourse = false;
	while (p)
	{
		if (strcmp(p -> info.b.cNo, t) == 0)
		{
			haveCourse = true;
			#define aa p -> info.a
			printf("%s %s %s %s ", aa.sNo, aa.sName, aa.sex ? "F" : "M", aa.major ? "A" : "S");
			#undef aa
			#define aa p -> info.b
			printf("%s %s %d %d\n", aa.cNo, aa.cName, aa.classHours, p -> info.score);
			#undef aa
		}
		p = p -> nxt;
	}

	if (!haveCourse) puts("Didn't find the course...");
	return ;
}

void getFailedStudent()
{
	printf("请输入查询的课程号：");
	char t[10];
	scanf("%s", t);
	reportList *p = rlist;

	bool haveCourse = false, haveFailed = false;
	while (p)
	{
		if (strcmp(p -> info.b.cNo, t) == 0)
		{
			haveCourse = true;
			if (p -> info.score < 60)
			{
				haveFailed = true;
				#define aa (p -> info.a)
				printf("%s %s %s %s ", aa.sNo, aa.sName, aa.sex ? "F" : "M", aa.major ? "A" : "S");
				#undef aa
				#define aa (p -> info.b)
				printf("%s %s %d %d\n", aa.cNo, aa.cName, aa.classHours, p -> info.score);
				#undef aa
			}
		}
		p = p -> nxt;
	}

	if (!haveCourse) puts("Didn't find the course...");
	else if (haveFailed) puts("No failed students!");
	return ;
}

Student sta[20]; int top;

void reverseStudentLink()
{
	studentList * p = slist;
	while (p)
	{
		sta[++top] = p -> info;
		p = p -> nxt;
	}

	studentList *np = NULL, *pre;
	while (top)
	{
		if (!np)
		{
			np = (studentList*)malloc(sizeof(studentList));
			np -> info = sta[top];
			np -> nxt = NULL;
			pre = np;
		}
		else
		{
			p = (studentList*)malloc(sizeof(studentList));
			p -> info = sta[top];
			p -> nxt = NULL;
			pre -> nxt = p;
			pre = p;
		}

		--top;
	}

	p = np;
	while (p)
	{
		#define aa (p -> info)
		printf("%s %s %s %s\n", aa.sNo, aa.sName, aa.sex ? "F" : "M", aa.major ? "A" : "S");
		#undef aa
		p = p -> nxt;
	}
	return ;
}

reportList *head, *tail;

void generateReportLink_queue()
{
	FILE *fp = fopen("courseGrade.dat", "r");

	if (fp == NULL)
	{
		puts("文件打开失败");
		return ;
	}

	int t, i;

	rlist = NULL; rlist_last = NULL;
	for (i = 1; i <= 30; i++)
	{
		reportList *a = (reportList *)malloc(sizeof(reportList));
		a -> nxt = NULL;
		fscanf(fp, "%s", (a -> info.a).sNo);
		fscanf(fp, "%s", (a -> info.b).cNo);
		fscanf(fp, "%d", &(a -> info.score));

		studentList *b = slist;
		while (b)
		{
			if (strcmp(b -> info.sNo, (a -> info.a).sNo) == 0)
				break;
			b = b -> nxt;
		}

		memcpy((a -> info.a).sName, b -> info.sName, sizeof(b -> info.sName));
		(a -> info.a).sex = b -> info.sex;
		(a -> info.a).major = b -> info.major;

		courseList *c = clist;
		while (c)
		{
			if (strcmp(c -> info.cNo, (a -> info.b).cNo) == 0)
				break;
			c = c -> nxt;
		}

		memcpy((a -> info.b).cName, c -> info.cName, sizeof(c -> info.cName));
		a -> info.b.classHours = c -> info.classHours;

		if (rlist == NULL)
		{
			rlist = a;
			rlist_last = a;
		}
		else
		{
			reportList *p = rlist, *pre = NULL;
			while (p)
			{
				int tmp = strcmp(p -> info.b.cNo, a -> info.b.cNo);
				if (tmp > 0 || (!tmp && p -> info.score < a -> info.score))
					break;
				pre = p;
				p = p -> nxt;
			}
			if (!pre)
			{
				a -> nxt = rlist;
				rlist = a;
			}
			else if (pre == rlist_last)
			{
				rlist_last -> nxt = a;
				rlist_last = a;
			}
			else
			{
				pre -> nxt = a;
				a -> nxt = p;
			}
		}
	}

	puts("操作成功");
	head = (reportList*)malloc(sizeof(reportList));
	tail = head;
	reportList *p = rlist, *q;
	while (p)
	{
		q = (reportList*)malloc(sizeof(reportList));
		*q = *p;
		q -> nxt = NULL;
		tail -> nxt = q;
		tail = q;
		p = p -> nxt;
	}

	p = head -> nxt;
	while (p)
	{
		#define aa p -> info.a
		printf("%s %s %s %s ", aa.sNo, aa.sName, aa.sex ? "F" : "M", aa.major ? "A" : "S");
		#undef aa
		#define aa p -> info.b
		printf("%s %s %d %d\n", aa.cNo, aa.cName, aa.classHours, p -> info.score);
		#undef aa

		head -> nxt = p -> nxt;
		free(p);
		p = head -> nxt;
	}
	return ;
}

int main()
{
	while (1)
	{
		char opt[3];

		outputMenu();
		printf("输入您的选择：");
		scanf("%s", opt);

		switch (opt[0])
		{
			case '1': inputStudentInfo();break;
			case '2': inputCourseInfo();break;
			case '3': inputGradeInfo();break;
			case '4': rwGenerateStudentLink();break;
			case '5': rwGenerateCourseLink();break;
			case '6': rwGenerateGradeLink();break;
			case '7': generateReportLink();break;
			case '8': generatePartReportLink();break;
			case '9': getFailedStudent();break;
			case 'a': reverseStudentLink();break;
			case 'b': generateReportLink_queue();break;
			default: return 0;
		}
		puts("");
	}
	return 0;
}
