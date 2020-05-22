#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#define N 100
#define PRO 3
#define CON 4

int buf[N], head, tail;
int pro_id[PRO], con_id[CON];
sem_t empty, full, mutex;
pthread_t pro[PRO], con[CON];

void randSleep()
{
	sleep(rand() % 5 + 1);
	return ;
}

int produce(int y)
{
	int x;
	randSleep();
	scanf("%d", &x);
	printf("Producer %d produced an item %d.\n", y, x);
	return x;
}

void consume(int y, int x)
{
	randSleep();
	printf("\t\tConsumer %d consumed an item %d!\n", y, x);
	return ;
}

void producer(void* arg)
{
	int y = *(int *)arg;
	printf("Producer %d init.\n", y);
	for (int i = 1; i <= 1000; i++)
	{
		int x = produce(y);
		sem_wait(&empty);
		sem_wait(&mutex);
		buf[tail] = x;
		tail = (tail + 1) % N;
		sem_post(&mutex);
		sem_post(&full);
	}
	printf("Producer %d exit.\n", y);
	return ;
}

void consumer(void* arg)
{
	int y = *(int *)arg;
	printf("Consumer %d init.\n", y);
	for (int i = 1; i <= 750; i++)
	{
		sem_wait(&full);
		sem_wait(&mutex);
		int x = buf[head];
		head = (head + 1) % N;
		sem_post(&mutex);
		sem_post(&empty);
		consume(y, x);
	}
	printf("Consumer %d exit.\n", y);
	return ;
}

int main()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < PRO; i++) pro_id[i] = i + 1;
	for (int i = 0; i < CON; i++) con_id[i] = i + 1;
	sem_init(&empty, 0, N);
	sem_init(&full, 0, 0);
	sem_init(&mutex, 0, 1);
	for (int i = 0; i < PRO; i++)
		pthread_create(&pro[i], NULL, (void *)producer, &pro_id[i]);
	for (int i = 0; i < CON; i++)
		pthread_create(&con[i], NULL, (void *)consumer, &con_id[i]);
	for (int i = 0; i < PRO; i++)
		pthread_join(pro[i], NULL);
	for (int i = 0; i < CON; i++)
		pthread_join(con[i], NULL);
	sem_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	return 0;
}