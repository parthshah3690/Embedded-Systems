#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	int servSock, clientSock, recvMsgSize;
	struct sockaddr_in servAddr, clntAddr;
	char echoBuffer[BUFSIZ + 1] = {0};

	// Create a server socket
	if((servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("Error in creating a socket\n");
		exit(-1);
	}

	// Assign a port to a socket
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(1234);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// Bind the socket
	if(bind(servSock, (struct sockaddr*) &servAddr, sizeof(servAddr)) < 0)
	{
		perror("Error in binding a socket\n");
		close(servSock);
		exit(-1);
	}

	// Listen the sockets
	if(listen(servSock, 5) < 0)
	{
		perror("Error in listening to a socket\n");
		close(servSock);
		exit(-1);
	}

	// Run forever
	for(;;)
	{
		if((clientSock = accept(servSock, (struct sockaddr*) &clntAddr, NULL)) < 0)
		{
			perror("Error in accepting a socket\n");
			close(servSock);
			exit(-1);
		}

		// Client is connected
		if((recvMsgSize = recv(clientSock, echoBuffer, BUFSIZ, 0)) < 0)
		{
			perror("Error in reception\n");
			close(clientSock);
			exit(-1);
		}

		while(recvMsgSize > 0)
		{
			if(send(clientSock, echoBuffer, recvMsgSize, 0) != recvMsgSize)
			{
				perror("Send failed\n");
				close(clientSock);
				exit(-1);
			}

			if((recvMsgSize = recv(clientSock, echoBuffer, BUFSIZ, 0)) < 0)
			{
				perror("Error in reception\n");
				close(clientSock);
				exit(-1);
			}
		}
	}

	close(clientSock);

	return 0;
}
