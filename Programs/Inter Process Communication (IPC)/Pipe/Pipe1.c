#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void writer(FILE* fp, const char* str, int count)
{
	for( ; count > 0; count--)
	{
		/* Write a mesage to a stream */
		fprintf(fp, "%s\n", str);
		fflush(fp);
		/* sleep for a while */
		sleep(1);
	}
}

void reader(FILE* fp)
{
	char buffer[1024];
	while(!feof(fp) && !ferror(fp) && (fgets(buffer, sizeof(buffer), fp) != NULL))
	{
		fputs(buffer, stdout);;
	}
}


int main(int argc, char **argv)
{
	int retPipe = 0;
	int fds[2];
	pid_t pid;

	/* Create a pipe. File descriptor for the two ends of the pipe
	 * are placed in fds
	 * fds[0] - read fd
	 * fds[1] - write fd
	 */
	retPipe = pipe(fds);
	if(retPipe == -1)
	{
		perror("Pipe creation failed\n");
		exit(-1);
	}

	/* Fork the process and create a child */
	pid = fork();
	if(pid == -1)
	{
		perror("Fork failed");
		/* close fds */
		close(fds[0]);
		close(fds[1]);
		exit(-1);
	}

	if(pid == 0)
	{
		FILE* fp;
		/* This is client process */
		/* close write fd */
		close(fds[1]);

		fp = fdopen(fds[0], "r");
		reader(fp);
		close(fds[0]);
	}
	else
	{
		FILE* fp;
		/* This is parent process */
		/* close read fd */
		close(fds[0]);

		fp = fdopen(fds[1], "w");
		writer(fp, "Hello Parth", 5);
		close(fds[1]);
		wait(NULL);
	}

	return 0;
}
