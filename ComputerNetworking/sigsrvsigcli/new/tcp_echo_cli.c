// Author: HeRaNO
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

void echo_rqt(int confd)
{
	while (fgets(buf, MAX_CMD_STR, stdin) != NULL)
	{
		int len = strlen(buf);
		buf[len - 1] = '\0';
		if (!strncmp(buf, "exit", 4)) break;
		int nlen = htonl(len);
		write(confd, &nlen, sizeof(int));
		write(confd, buf, len);
		memset(buf, 0, sizeof buf);
		int head = 0;
		read(confd, &nlen, sizeof(int));
		len = ntohl(nlen);
		while (len)
		{
			int ret = read(confd, buf + head, len);
			head += ret; len -= ret;
		}
		printf("[echo_rep] %s\n", buf);
	}
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
	memset(&srv, 0, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr(argv[1]);
	srv.sin_port = htons(atoi(argv[2]));
	do {
		int ret = connect(confd, (struct sockaddr *) &srv, sizeof(struct sockaddr));
		if (!~ret && errno == EINTR) continue;
		if (!ret)
		{
			printf("[cli] server[%s:%s] is connected!\n", argv[1], argv[2]);
			echo_rqt(confd);
		}
	} while (0);
	leave(confd);
	printf("[cli] client is exiting!\n");
	return 0;
}
