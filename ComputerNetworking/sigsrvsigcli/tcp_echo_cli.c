#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define MAX_CMD_STR 100

char buf[MAX_CMD_STR + 1];

void echo_rqt(int confd, char* buf, int len)
{
	write(confd, &len, sizeof(int));
	write(confd, buf, len);
	read(confd, &len, sizeof(int));
	read(confd, buf, len);
	printf("[echo_rep] %s\n", buf);
	return ;
}

void leave(int confd)
{
	close(confd);
	printf("[cli] connfd is closed!\n");
	return ;
}

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <IP> <PORT>\n", argv[0]);
		return 0;
	}

	int confd = socket(AF_INET, SOCK_STREAM, 0);
	if (confd < 0)
	{
		perror("socket");
		return 1;
	}
	struct sockaddr_in srv;
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr(argv[1]);
	srv.sin_port = htons(atoi(argv[2]));
	if (connect(confd, (struct sockaddr*) &srv, sizeof(srv)) < 0)
	{
		perror("connect");
		return 4;
	}
	printf("[cli] server[%s:%s] is connected!\n", argv[1], argv[2]);
	while (fgets(buf, MAX_CMD_STR, stdin) != NULL)
	{
		int l = strnlen(buf, MAX_CMD_STR);
		buf[l - 1] = '\0';
		if (!strncmp(buf, "exit", 4)) break;
		echo_rqt(confd, buf, l);
	}
	leave(confd);
	printf("[cli] client is exiting!\n");
	return 0;
}
