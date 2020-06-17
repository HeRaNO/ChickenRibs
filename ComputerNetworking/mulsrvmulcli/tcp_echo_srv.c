// Author: HeRaNO
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define writeToFile(__FILE, FORMAT, ...)        \
	{                                           \
		printf(FORMAT, ##__VA_ARGS__);          \
		fprintf(__FILE, FORMAT, ##__VA_ARGS__); \
		fflush(__FILE);                         \
	}

#define MAX_CMD_STR 100

struct message
{
	uint32_t pin;
	uint32_t len;
	char msg[MAX_CMD_STR + 1];
};

int sigtype, leave;

void sendMsg(int confd, struct message * buf)
{
	int len = buf -> len + 8;
	buf -> pin = htonl(buf -> pin);
	buf -> len = htonl(buf -> len);
	write(confd, buf, len);
	return ;
}

int recvMsg(int confd, struct message * buf)
{
	memset(buf, 0, sizeof(struct message));
	int head = 0, len;
	if (!read(confd, &buf -> pin, sizeof(uint32_t))) return 0;
	if (!read(confd, &buf -> len, sizeof(uint32_t))) return 0;
	buf -> pin = ntohl(buf -> pin);
	buf -> len = ntohl(buf -> len);
	len = buf -> len;
	while (len)
	{
		int ret = read(confd, buf -> msg + head, len);
		if (ret < 0) return 0;
		head += ret; len -= ret;
	}
	return head;
}

uint32_t echo_rep(int confd, FILE * out)
{
	struct message *buf = (struct message *)malloc(sizeof (struct message));
	memset(buf, 0, sizeof (struct message));
	uint32_t pin = 0;
	while (1)
	{
		if (!recvMsg(confd, buf))
		{
			if (errno == EINTR)
			{
				if (leave) break;
				continue;
			}
			break;
		}
		pin = buf -> pin;
		writeToFile(out, "[echo_rqt](%d) %s\n", getpid(), buf -> msg);
		sendMsg(confd, buf);
	}
	free(buf);
	return pin;
}

void server(int confd)
{
	char fname[32], nfname[32];
	memset(fname, 0, sizeof fname);
	memset(nfname, 0, sizeof nfname);

	sprintf(fname, "stu_srv_res_%d.txt", getpid());
	FILE *out = fopen(fname, "wb");
	printf("[srv](%d) stu_srv_res_%d.txt is opened!\n", getpid(), getpid());
	
	uint32_t pin = echo_rep(confd, out);

	close(confd);
	writeToFile(out, "[srv](%d) connfd is closed!\n", getpid());
	fclose(out);
	printf("[srv](%d) stu_srv_res_%d.txt is closed!\n", getpid(), getpid());

	sprintf(nfname, "stu_srv_res_%u.txt", pin);
	rename(fname, nfname);
	printf("[srv](%d) res file rename done!\n", getpid());
	exit(EXIT_SUCCESS);
}

void sig_pipe(int sig)
{
	sigtype = sig;
	fprintf(stderr, "[srv](%d) SIGPIPE is coming!\n", getpid());
	return ;
}

void sig_int(int sig) // must keep same with it!!!
{
	leave = 1; sigtype = sig;
	printf("[srv](%d) SIGINT is coming!\n", getpid());
	return ;
}

void sig_child(int sig) // must keep same with it!!!
{
	sigtype = sig;
	int status = 0;
	pid_t ch = 0, pa = getpid();
	fprintf(stderr, "[srv](%d) SIGCHLD is coming!\n", pa);
	while ((ch = waitpid(-1, &status, WNOHANG)) > 0)
	{
		fprintf(stderr, "[srv](%d) child process(%d) terminated.\n", pa, ch);
		sched_yield();
	}
	return ;
}

void initSignal()
{
	struct sigaction reactPIPE, oldReactPIPE;
	reactPIPE.sa_handler = sig_pipe;
	sigemptyset(&reactPIPE.sa_mask);
	reactPIPE.sa_flags = SA_RESTART;
	sigaction(SIGPIPE, &reactPIPE, &oldReactPIPE);

	struct sigaction reactINT, oldReactINT;
	reactINT.sa_handler = sig_int;
	sigemptyset(&reactINT.sa_mask);
	reactINT.sa_flags = 0;
	sigaction(SIGINT, &reactINT, &oldReactINT);

	struct sigaction reactChild, oldReactChild;
	reactChild.sa_handler = sig_child;
	sigemptyset(&reactChild.sa_mask);
	reactChild.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &reactChild, &oldReactChild);
	return ;
}

int main(int argc, char const *argv[])
{
	if (argc != 3)
	{
		printf("Usage: %s <IP> <Port>\n", argv[0]);
		return 0;
	}
	
	initSignal();

	FILE * out = fopen("stu_srv_res_p.txt", "wb");
	printf("[srv](%d) stu_srv_res_p.txt is openend!\n", getpid());

	struct sockaddr_in srv;
	memset(&srv, 0, sizeof(struct sockaddr_in));
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr  = inet_addr(argv[1]);
	srv.sin_port = htons(atoi(argv[2]));

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd < 0)
	{
		perror("socket");
		return 1;
	}

	writeToFile(out, "[srv](%d) server[%s:%s] is initializing!\n", getpid(), argv[1], argv[2])

	if (bind(listenfd, (struct sockaddr *) &srv, sizeof(srv)) != 0)
	{
		perror("bind");
		return 1;
	}
	if (listen(listenfd, 32))
	{
		perror("listen");
		return 1;
	}
	while (!leave)
	{
		struct sockaddr_in remote;
		socklen_t len = sizeof(remote);
		memset(&remote, 0, len);
		int confd = accept(listenfd, (struct sockaddr *) &remote, &len);
		if (confd < 0 && errno == EINTR)
		{
			if (sigtype == SIGINT) break;
			continue;
		}
		int cport = ntohs(remote.sin_port);
		char cip[32];
		inet_ntop(AF_INET, &remote.sin_addr, cip, sizeof(cip));
		writeToFile(out, "[srv](%d) client[%s:%d] is accepted!\n", getpid(), cip, cport);
		if (!fork())
		{
			/* Child */
			close(listenfd);
			server(confd);
		}
		else close(confd);
	}
	close(listenfd);
	writeToFile(out, "[srv](%d) listenfd is closed!\n", getpid());
	fclose(out);
	printf("[srv](%d) stu_srv_res_p.txt is closed!\n", getpid());
	return 0;
}
