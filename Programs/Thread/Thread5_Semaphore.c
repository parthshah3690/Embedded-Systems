#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaphore1;
sem_t semaphore2;

void* thread1_handler(void* arg)
{
	int i = 0;
	while (i <= 20)
	{
		sem_wait(&semaphore1);
		printf("%d\n", i);
		i = i + 2;
		sem_post(&semaphore2);
	}

	return NULL;
}

void* thread2_handler(void* arg)
{
	int i = 1;
	while (i <= 20)
	{
		sem_wait(&semaphore2);
		printf("%d\n", i);
		i = i + 2;
		sem_post(&semaphore1);
	}

	return NULL;
}


int main(int argc, char **argv)
{
	pthread_t t1, t2;

	sem_init(&semaphore1, 0, 1);
	sem_init(&semaphore2, 0, 0);

	pthread_create(&t1, NULL, thread1_handler, NULL);
	pthread_create(&t2, NULL, thread2_handler, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	sem_destroy(&semaphore1);
	sem_destroy(&semaphore2);

	return 0;
}
