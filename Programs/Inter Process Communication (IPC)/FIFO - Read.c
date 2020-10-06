#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

/* Open terminal and execute cat > /tmp/myfifo */
/* You can also write an application to write a data to fifo */

int main(int argc, char **argv)
{
	char buffer[4096];
	int fd = 0, ret;
	if (mkfifo("/tmp/myfifo", 0666) == -1)
	{
		perror("Error in creating FIFO\n");
		exit(-1);
	}

	fd = open("/tmp/myfifo", O_RDONLY);
	while(1)
	{
		ret = read(fd, buffer, sizeof(buffer));
		if(ret == -1)
		{
			break;
		}
		write(STDOUT_FILENO, buffer, ret);
	}
	close(fd);
}
