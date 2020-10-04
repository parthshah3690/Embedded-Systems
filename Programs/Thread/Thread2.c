#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/* Observation : By using pthread_join function, the main program waits for the thread to complete its work and return the value */

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
	pthread_join(thread_id, NULL);
	printf("Exiting from program\n");
	return 0;
}
