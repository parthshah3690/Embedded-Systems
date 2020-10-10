#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <netdb.h>

void AppCloseSocket(int socketFd)
{
	shutdown(socketFd, SHUT_RDWR);
	close(socketFd);
}

int main(int argc, char **argv)
{
	int servsockfd, clientsockfd, readSize,reuseflag = 1;
	struct sockaddr_in server_address, client_address;
	socklen_t clientLen = sizeof (struct sockaddr_in);
	char buffer[BUFSIZ + 1];

	if ((servsockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Not able to create socket\n");
		exit(-1);
	}

	setsockopt (servsockfd, SOL_SOCKET, SO_REUSEADDR, (int *)&reuseflag, sizeof(int));

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = INADDR_ANY;
	server_address.sin_port = htons(1256);

	printf("Bind\n");
	if(bind(servsockfd, (const struct sockaddr*) &server_address, sizeof(server_address)) != 0)
	{
		perror("Unable to bind\n");
		AppCloseSocket(servsockfd);
		exit(-1);
	}

	printf("Listen\n");
	if (listen(servsockfd, 5) != 0)
	{
		perror("Listen failed\n");
		AppCloseSocket(servsockfd);
		exit(-1);
	}

	struct hostent* host = NULL;
	char** names;
	host = gethostbyname("Google.com");
	names = host->h_aliases;
	while(*names)
	{
		printf("%s ",*names);
		names++;
	}

	printf("Accept\n\n");
	clientsockfd = accept(servsockfd, (struct sockaddr*) &client_address, &clientLen);
	if(clientsockfd == -1)
	{
		perror ("Accept failed\n");
		AppCloseSocket(servsockfd);
		exit(-1);
	}



	while(1)
	{
		readSize = recv(clientsockfd, &buffer, BUFSIZ, MSG_NOSIGNAL);
		if(readSize != 0)
		{
			if(strncmp(buffer, "end", 3) == 0)
			{
				break;
			}
			printf("%s\n", buffer);
		}
	}

	printf("GoodBye from Server\n");
	AppCloseSocket(servsockfd);

	exit(0);
}


