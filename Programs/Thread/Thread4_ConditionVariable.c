#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static const int maxCount = 100;
static int count = 0;

void* thread1_handler(void* arg)
{
	while(1)
	{
		// Lock the mutex
		pthread_mutex_lock(&mutex);
		if (count % 2 != 0)
		{
			// count value is odd, hence wait here
			pthread_cond_wait(&cond, &mutex);
		}
		count++;
		printf("%d\n", count);
		pthread_cond_signal(&cond);
		if (count >= maxCount)
		{
			pthread_mutex_unlock(&mutex);
			return NULL;
		}

		pthread_mutex_unlock(&mutex);

	}
	return NULL;
}

void* thread2_handler(void* arg)
{
	while(1)
	{
		// Lock the mutex
		pthread_mutex_lock(&mutex);
		if (count % 2 == 0)
		{
			pthread_cond_wait(&cond, &mutex);
		}
		count++;
		printf("%d\n", count);
		pthread_cond_signal(&cond);
		if (count >= maxCount)
		{
			pthread_mutex_unlock(&mutex);
			return NULL;
		}

		pthread_mutex_unlock(&mutex);

	}
	return NULL;
}


int main(int argc, char **argv)
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, thread1_handler, NULL);
	pthread_create(&t2, NULL, thread2_handler, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);

	return 0;
}
