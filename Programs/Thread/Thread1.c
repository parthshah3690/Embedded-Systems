#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Observation : Here the program exists without waiting for the thread to complete its task */


void* thread_handler(void* arg)
{
	for(int i = 0; i < 5; i++)
	{
		printf("%d\n", i);
		sleep(1);
	}
	printf("Exiting from thread handler\n");

	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t thread_id;
	pthread_create(&thread_id, NULL, &thread_handler, NULL);
	printf("Exiting from program\n");
	return 0;
}
