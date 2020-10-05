#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Create Mutual Exclusion object that will be shared among two threads
pthread_mutex_t mutex;
static int count = 0;

void* thread_handler1(void* arg)
{
	while (count <= 10)
	{
		pthread_mutex_lock(&mutex);
		printf("Thread1--> Count value : %d\n", count++);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	return NULL;
}

void* thread_handler2(void* arg)
{
	while (count <= 10)
	{
		pthread_mutex_lock(&mutex);
		printf("Thread2--> Count value : %d\n", count++);
		pthread_mutex_unlock(&mutex);
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


	// initialize mutex object
	pthread_mutex_init(&mutex, NULL);
	// Create 2 threads

	for(int i = 0; i < 2; i++)
	{
		pthread_create(&thread_id[i], &attr, fp[i], NULL);
	}

	for (int i = 0; i < 2; i++)
	{
		pthread_join(thread_id[i], NULL);
	}

	// Destroy mutex object
	pthread_mutex_destroy(&mutex);
	// Destroy thread attributes
	pthread_attr_destroy(&attr);
	return 0;
}
