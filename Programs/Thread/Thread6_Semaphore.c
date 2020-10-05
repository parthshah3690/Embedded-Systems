#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore;
#define COUNT 100
static int count = 0;

void* producer(void* arg)
{
	while (count < 100)
	{
		count++;
		sem_post(&semaphore);
		sleep(1);
	}

	return NULL;
}

void* consumer(void* arg)
{
	int i = 1;
	while (i <= 20)
	{
		sem_wait(&semaphore);
		printf("%d\n", count);
	}

	return NULL;
}


int main(int argc, char **argv)
{
	pthread_t t1, t2;

	sem_init(&semaphore, 0, 0);

	pthread_create(&t1, NULL, producer, NULL);
	pthread_create(&t2, NULL, consumer, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	sem_destroy(&semaphore);

	return 0;
}
