#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

// Create Mutual Exclusion object that will be shared among two threads
sem_t semaphore;
static int count = 0;

void* thread_handler1(void* arg)
{
	while (count <= 10)
	{
		sem_wait(&semaphore);
		printf("Thread1--> Count value : %d\n", count++);
		sem_post(&semaphore);
		sleep(1);
	}

	return NULL;
}

void* thread_handler2(void* arg)
{
	while (count <= 10)
	{
		sem_wait(&semaphore);
		printf("Thread2--> Count value : %d\n", count++);
		sem_post(&semaphore);
		sleep(1);
	}

	return NULL;
}

void* (*fp[])(void*) = {thread_handler1, thread_handler2};

int main(int argc, char **argv)
{
	// Array to hold 2 Thread Ids
	pthread_t thread_id[2];

	// Create thread attribute, By default detachstate for a thread will be always PTHREAD_CREATE_JOINABLE
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);


	// initialize semaphore object
	sem_init(&semaphore, 0, 1);
	// Create 2 threads

	for(int i = 0; i < 2; i++)
	{
		pthread_create(&thread_id[i], &attr, fp[i], NULL);
	}

	for (int i = 0; i < 2; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	// Destroy semaphore object
	sem_destroy(&semaphore);
	// Destroy thread attributes
	pthread_attr_destroy(&attr);
	return 0;
}
