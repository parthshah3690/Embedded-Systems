#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <arpa/inet.h>

// Global variables
char isRunning = 1;

void SigIntHandler (int signum)
{
	isRunning = 0;
}

void CloseSocket (int socketfd)
{
    if (socketfd != -1)
    {
        shutdown (socketfd, SHUT_RDWR);
        close (socketfd);
        socketfd = -1;
    }
    return;
}

void* processRequestThread(void* arg)
{
	char buffer[BUFSIZ + 1] = { 0 };
	int sockId = *((int*) arg);
	int recvSize = 0;

	while (recvSize >= 0)
	{
		recvSize = recv(sockId, buffer, BUFSIZ, MSG_NOSIGNAL);
		printf ("%s:%d Received Buffer : %s\n", __PRETTY_FUNCTION__, __LINE__, buffer);
	}
	return NULL;
}

void* acceptConnectionsThread(void* arg)
{
    int clientSockId = -1;
    socklen_t clientLen = sizeof (struct sockaddr_in);
    struct sockaddr_in clientAddrss;
    int sockId = *((int*)arg);

    while (isRunning)
    {
		printf ("%s :%d Waiting for client to send request........\n", __PRETTY_FUNCTION__, __LINE__);
        clientSockId = accept (sockId, (struct sockaddr *)&clientAddrss, &clientLen);
        if (clientSockId == -1)
        {
            printf ("%s:%d Accept connection failed, socket might be closed!", __PRETTY_FUNCTION__, __LINE__);
            break;
        }

        printf ("%s:%d Client connection with socket id %d ", __PRETTY_FUNCTION__, __LINE__, clientSockId);
		pthread_t thread_id;
        pthread_attr_t attr;
        pthread_attr_init (&attr);
        pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);

		if (pthread_create (&thread_id, &attr, processRequestThread, (void*)&clientSockId) != 0)
		{
			printf ("%s:%d Failed to create thread to accept connections", __PRETTY_FUNCTION__, __LINE__);
			pthread_attr_destroy (&attr);
			CloseSocket (clientSockId);
			break;
		}
    }

	return NULL;
}

int main(int argc, char **argv)
{
	int serverSocket;
	pthread_t threadId = 0;
	struct sockaddr_in serverAddrss;
    int reuseflag = 1;

    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, &SigIntHandler);

    serverSocket= socket (AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
    {
        printf ("%s:%d Failed to create server socket", __PRETTY_FUNCTION__, __LINE__);
        return -1;
    }

    setsockopt (serverSocket, SOL_SOCKET, SO_REUSEADDR, (int *)&reuseflag, sizeof(int));

    memset (&serverAddrss, 0, sizeof(struct sockaddr_in));
    serverAddrss.sin_family = AF_INET;
    serverAddrss.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddrss.sin_port = htons (3333);

    if (bind(serverSocket, (struct sockaddr *)&serverAddrss, sizeof(struct sockaddr_in)) < 0)
    {
        printf ("%s:%d Failed to bind server socket", __PRETTY_FUNCTION__, __LINE__);
        CloseSocket (serverSocket);
        return -1;
    }

    if (listen(serverSocket, 5) != 0)
    {
        printf ("%s:%d Failed to listen server socket", __PRETTY_FUNCTION__, __LINE__);
        CloseSocket (serverSocket);
        return -1;
    }

	if (pthread_create (&threadId, NULL, acceptConnectionsThread, (void*) &serverSocket) != 0)
	{
		printf ("%s:%d Failed to create thread to accept connections", __PRETTY_FUNCTION__, __LINE__);
		CloseSocket (serverSocket);
		return -1;
    }

	pthread_join(threadId, NULL);

	return 0;
}
