#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

int main(int argc, char **argv)
{
	const char buffer[] = "This is fifo";
	int fd = 0;
	if (mkfifo("/tmp/myfifo", 0666) == -1)
	{
		perror("Error in creating FIFO\n");
		exit(-1);
	}

	while(1)
	{
		fd = open("/tmp/myfifo", O_WRONLY);
		write(fd, buffer, sizeof(buffer));
		close(fd);
		sleep(1);
	}
}
