// Author: HeRaNO
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>

#define MSG_KEY 111

struct Msgbuf
{
	long mtype;
	int content;
};

int main()
{
	int mspid;
	pid_t pid;

	mspid = msgget(MSG_KEY, IPC_CREAT | 0666);
	if(mspid == -1)
	{
		perror("msgget");
		exit(-1);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(-1);
	}
	else if (!pid)
	{
		/* Child */
		for (int i = 0; i < 100; i++)
		{
			int msqid = msgget(MSG_KEY, 0);
			if (msqid == -1)
			{
				perror("msgget");
				exit(-1);
			}
			struct Msgbuf buf;
			if (msgrcv(msqid, (void*) &buf, sizeof(struct Msgbuf), 1, 0) == -1)
			{
				perror("msgrcv");
				exit(-1);
			}
			printf("\t\tChild: received %d\n", buf.content);
		}
		printf("\t\tReceived OK!\n");
		exit(0);
	}
	else
	{
		/* Parent */
		int cnt = 0;
		while (cnt < 5)
		{
			for (int i = 0; i < 20; i++)
			{
				struct Msgbuf buf;
				buf.mtype = 1;
				buf.content = cnt * 20 + i;
				if (msgsnd(mspid, (const void*) &buf, sizeof(struct Msgbuf), 0) == -1)
				{
					perror("msgsnd");
					exit(-1);
				}
				printf("Parent: send %d\n", buf.content);
			}
			++cnt;
			sleep(1);
		}
		printf("Send OK!\n");
	}
	msgctl(mspid, IPC_RMID, NULL);
	return 0;
}
