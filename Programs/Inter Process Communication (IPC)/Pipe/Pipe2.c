#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

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
		/* This is child process */
		/* close write fd */
		close(fds[1]);

		/* Connect the read end of the pipe to standard input. */
		dup2(fds[0], STDIN_FILENO);
		/* Replace the child process with the "sort" program */
		execlp("sort", "sort", 0);
	}
	else
	{
		FILE* fp;
		/* This is parent process */
		/* close read fd */
		close(fds[0]);

		fp = fdopen(fds[1], "w");
		fprintf(fp, "This is Pipe program\n");
		fprintf(fp, "This is my second program\n");
		fprintf(fp, "InterProcess Communication\n");
		fprintf(fp, "Parth Shah\n");
		close(fds[1]);
		waitpid(pid, NULL, 0);
	}

	return 0;
}
