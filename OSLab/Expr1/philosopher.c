#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5

int id[N];
sem_t chopstick[N], mutex;
pthread_t phi[N];

void randSleep()
{
	sleep(rand() % 5 + 1);
	return ;
}

void think(int x, int t)
{
	printf("%d: Philosopher %d is thinking...\n", t, x);
	randSleep();
	return ;
}

void eat(int x, int t)
{
	printf("%d: Philosopher %d is eating!\n", t, x);
	randSleep();
	return ;
}

void philosopher(void *arg)
{
	int x = *(int *)arg;
	printf("Philosopher %d init.\n", x);
	int l = x - 1, r = x % N;
	int cnt = 100;
	for (int i = 1; i <= cnt; i++)
	{
		think(x, i);
		sem_wait(&mutex);
		sem_wait(&chopstick[l]);
		sem_wait(&chopstick[r]);
		sem_post(&mutex);
		eat(x, i);
		sem_post(&chopstick[r]);
		sem_post(&chopstick[l]);
	}
	printf("Philosopher %d exit.\n", x);
	return ;
}

int main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < N; i++) id[i] = i + 1;
	for (int i = 0; i < N; i++)
		if (sem_init(&chopstick[i], 0, 1) != 0)
			perror("init chopstick error");
	if (sem_init(&mutex, 0, N - 1) != 0)
		perror("init mutex error");
	for (int i = 0; i < N; i++)
		if (pthread_create(&phi[i], NULL, (void *)philosopher, &id[i]) != 0)
			perror("create thread error");
	for (int i = 0; i < N; i++)
		if (pthread_join(phi[i], NULL) != 0)
			perror("join thread error");
	for (int i = 0; i < N; i++)
		if (sem_destroy(&chopstick[i]) != 0)
			perror("destroy chopstick error");
	if (sem_destroy(&mutex) != 0)
		perror("destory mutex error");
	return 0;
}