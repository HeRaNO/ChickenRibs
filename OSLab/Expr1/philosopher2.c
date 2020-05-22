#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define N 5

int id[N];
sem_t chopstick[N];
pthread_mutex_t mutex;
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
		pthread_mutex_lock(&mutex);
		sem_wait(&chopstick[l]);
		sem_wait(&chopstick[r]);
		eat(x, i);
		pthread_mutex_unlock(&mutex);
		sem_post(&chopstick[l]);
		sem_post(&chopstick[r]);
	}
	printf("Philosopher %d exit.\n", x);
	return ;
}

int main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < N; i++) id[i] = i + 1;
	for (int i = 0; i < N; i++)
		sem_init(&chopstick[i], 0, 1);
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < N; i++)
		pthread_create(&phi[i], NULL, (void *)philosopher, &id[i]);
	for (int i = 0; i < N; i++)
		pthread_join(phi[i], NULL);
	for (int i = 0; i < N; i++)
		sem_destroy(&chopstick[i]);
	pthread_mutex_destroy(&mutex);
	return 0;
}