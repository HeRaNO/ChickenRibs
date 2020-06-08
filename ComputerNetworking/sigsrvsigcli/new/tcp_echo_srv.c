// Author: HeRaNO
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define MAX_CMD_STR 100

int leave, sigtype;
char buf[MAX_CMD_STR + 1];

void sig_pipe(int sig)
{
	sigtype = sig;
	printf("[srv] SIGPIPE is coming!\n");
	return ;
}

void sig_int(int sig) // must keep same with it!!!
{
	leave = 1; sigtype = sig;
	printf("[srv] SIGINT is coming!\n");
	return ;
}

int readWithErr(int confd, void * cont, int len)
{
	int ret = read(confd, cont, len);
	if (ret < 0)
	{
		printf("[srv] read data return %d and errno is %d\n", ret, errno);
		if (errno == EINTR)
		{
			if (sigtype == SIGINT) return -1;
			return -1;
		}
	}
	return ret;
}

void echo_rep(int confd)
{
	int nlen = 0;
	do {
		int ret = readWithErr(confd, &nlen, sizeof(int));
		if (!~ret || !ret) break;
		else if (ret < 0) continue;
		memset(buf, 0, sizeof buf);
		int len = ntohl(nlen);
		int head = 0;
		while (len)
		{
			int ret = readWithErr(confd, buf + head, len);
			if (!ret) return ;
			else if (ret < 0) continue;
			head += ret; len -= ret;
		}
		len = ntohl(nlen);
		printf("[echo_rqt] %s\n", buf);
		write(confd, &nlen, sizeof(int));
		write(confd, buf, len);
	} while (1);
	return ;
}

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <IP> <PORT>\n", argv[0]);
		return 0;
	}
	struct sigaction reactPIPE;
	reactPIPE.sa_handler = sig_pipe;
	sigemptyset(&reactPIPE.sa_mask);
	reactPIPE.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &reactPIPE, NULL);

	struct sigaction reactINT;
	reactINT.sa_handler = sig_int;
	sigemptyset(&reactINT.sa_mask);
	reactINT.sa_flags = 0;
	sigaction(SIGINT, &reactINT, NULL);

	struct sockaddr_in local;
	memset(&local, 0, sizeof(struct sockaddr_in));
	local.sin_family = AF_INET;
	local.sin_addr.s_addr  = inet_addr(argv[1]);
	local.sin_port = htons(atoi(argv[2]));

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		perror("socket");
		return 4;
	}

	int opt = SOL_SOCKET;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	printf("[srv] server[%s:%s] is initializing!\n", argv[1], argv[2]);
	
	if (bind(listenfd, (struct sockaddr *) &local, sizeof(local)) != 0)
	{
		perror("bind");
		return 5;
	}
	if (listen(listenfd, 5))
	{
		perror("listen");
		return 6;
	}
	struct sockaddr_in remote;
	socklen_t len = sizeof(remote);
	memset(&remote, 0, len);
	while (!leave)
	{
		int confd = accept(listenfd, (struct sockaddr *) &remote, &len);
		if (!~confd && sigtype == SIGINT && errno == EINTR) break;
		if (confd < 0) continue;
		printf("[srv] client[%s:%d] is accepted!\n", inet_ntoa(remote.sin_addr), ntohs(remote.sin_port));
		echo_rep(confd);
		close(confd);
		printf("[srv] connfd is closed!\n");
	}
	close(listenfd);
	printf("[srv] listenfd is closed!\n");
	printf("[srv] server is going to exit!\n");
	return 0;
}
