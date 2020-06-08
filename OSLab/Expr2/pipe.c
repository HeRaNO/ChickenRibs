// Author: HeRaNO
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#define MAXL 100

char buf[MAXL];

int main()
{
	pid_t pid;
	int fd[2];
	if (pipe(fd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		/* Child 1 */
		if (write(fd[1], "Child process 1 is sending a message!", 38) == -1)
		{
			perror("child 1 sending");
			exit(EXIT_FAILURE);
		}
		printf("Child 1 send OK\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		/* Parent */
		int status;
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
		if (read(fd[0], buf, MAXL) == -1)
		{
			perror("parent read child 1");
			exit(EXIT_FAILURE);
		}
		printf("Parent read child 1 ok: %s\n", buf);
	}
	pid = fork();
	if (pid == 0)
	{
		/* Child 2 */
		if (write(fd[1], "Child process 2 is sending a message!", 38) == -1)
		{
			perror("child 2 sending");
			exit(EXIT_FAILURE);
		}
		printf("Child 2 send OK\n");
		exit(EXIT_SUCCESS);
	}
	else
	{
		/* Parent */
		int status;
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
		if (read(fd[0], buf, MAXL) == -1)
		{
			perror("parent read child 2");
			exit(EXIT_FAILURE);
		}
		printf("Parent read child 2 ok: %s\n", buf);
	}
	close(fd[0]);
	close(fd[1]);
	return 0;
}