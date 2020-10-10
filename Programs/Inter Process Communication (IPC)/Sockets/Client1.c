#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char **argv)
{
	int clientSock;
	struct sockaddr_in servAddr;

	// Create a server socket
	if((clientSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	{
		perror("Error in creating a socket\n");
		exit(-1);
	}

	// Assign a port to a socket
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("192.168.0.104");
	servAddr.sin_port = htons(1234);

	// connect to server
	if(connect(clientSock, (struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
	{
		perror("Error in Connect to a server\n");
		close(clientSock);
		exit(-1);
	}

	// Run forever
	for(;;)
	{
		send(clientSock, "Hello from Client", strlen("Hello from Client"), 0);
		sleep(1);
	}


	close(clientSock);

	return 0;
}
