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
#define MAX_CMD_STR 100
#define writeToFile(__FILE, FORMAT, ...)        \
	{                                           \
		printf(FORMAT, ##__VA_ARGS__);          \
		fprintf(__FILE, FORMAT, ##__VA_ARGS__); \
		fflush(__FILE);                         \
	}

int sigtype;

// Change char array to struct, but have more issue than imagined.
struct message
{
	uint32_t pin;
	uint32_t len;
	char msg[MAX_CMD_STR + 1];
};

int isExit(const char * buf)
{
	if (buf == NULL) return 0;
	return strncmp(buf, "exit", 4) == 0;
}

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

void echo_rqt(int confd, FILE * out, int pin)
{
	char fname[32];
	memset(fname, 0, sizeof fname);
	sprintf(fname, "td%d.txt", pin);
	FILE * in = fopen(fname, "r");
	struct message *buf = (struct message *)malloc(sizeof (struct message));
	memset(buf, 0, sizeof (struct message));
	while (fgets(buf -> msg, MAX_CMD_STR + 1, in) != NULL)
	{
		if (isExit(buf -> msg)) break; // Must here
		buf -> pin = pin;
		buf -> len = strlen(buf -> msg);
		buf -> msg[buf -> len - 1] = '\0';
		sendMsg(confd, buf);
		memset(buf, 0, sizeof(struct message));
		recvMsg(confd, buf);
		writeToFile(out, "[echo_rep](%d) %s\n", getpid(), buf -> msg);
	}
	fclose(in);
	free(buf);
	return ;
}

void client(int pin, struct sockaddr_in srv, const char * IP, const char * port)
{
	char fname[32];
	memset(fname, 0, sizeof fname);
	sprintf(fname, "stu_cli_res_%d.txt", pin);
	FILE *client_out = fopen(fname, "wb");
	printf("[cli](%d) stu_cli_res_%d.txt is created!\n", getpid(), pin);
	int confd = socket(AF_INET, SOCK_STREAM, 0);
	if (confd < 0)
	{
		perror("socket");
		return ;
	}
	while (1)
	{
		int ret = connect(confd, (struct sockaddr *)&srv, sizeof(srv));
		if (!ret)
		{
			writeToFile(client_out, "[cli](%d) server[%s:%s] is connected!\n", getpid(), IP, port);
			echo_rqt(confd, client_out, pin);
			break;
		}
		else break;
	}
	close(confd);
	writeToFile(client_out, "[cli](%d) connfd is closed!\n", getpid());
	writeToFile(client_out, "[cli](%d) %s process is going to exit!\n",
				getpid(),
				pin == 0 ? "parent" : "child");
	fclose(client_out);
	printf("[cli](%d) stu_cli_res_%d.txt is closed!\n", getpid(), pin);
	return ;
}

void sig_pipe(int sig)
{
	sigtype = sig;
	fprintf(stderr, "[cli](%d) SIGPIPE is coming!\n", getpid());
	return ;
}

void sig_child(int sig) // must keep same with it!!!
{
	sigtype = sig;
	int status = 0;
	pid_t ch = 0, pa = getpid();
	fprintf(stderr, "[cli](%d) SIGCHILD is coming!\n", pa);
	while ((ch = waitpid(-1, &status, WNOHANG)) > 0)
	{
		fprintf(stderr, "[cli](%d) child process(%d) terminated.\n", pa, ch);
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

	struct sigaction reactChild, oldReactChild;
	reactChild.sa_handler = sig_child;
	sigemptyset(&reactChild.sa_mask);
	reactChild.sa_flags = SA_RESTART;
	sigaction(SIGCHLD, &reactChild, &oldReactChild);
	return ;
}

int main(int argc, char const *argv[])
{
	if (argc != 4)
	{
		printf("Usage: %s <IP> <Port> <Concurrency>\n", argv[0]);
		return 0;
	}

	initSignal();

	struct sockaddr_in srv;
	memset(&srv, 0, sizeof(srv));
	srv.sin_family = AF_INET;
	srv.sin_addr.s_addr = inet_addr(argv[1]);
	srv.sin_port = htons(atoi(argv[2]));

	int concnt = atoi(argv[3]), pin;

	for (pin = 1; pin < concnt; pin++)
		if (!fork()) break;
	if (pin == concnt) pin = 0;
	client(pin, srv, argv[1], argv[2]);
	return 0;
}
