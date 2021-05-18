#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define BUF_SIZE 512

void error(const char *msg)
{
	perror(msg);
	exit(1);
}


int main(int argc, char *argv[])
{
	int socket_serv, socket_client;
	socklen_t client_len;
	int port = 1313;

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int n;
	socket_serv = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);
	client_len = sizeof(client_addr);
	
	if (bind(socket_serv, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		error("ERROR on binding");
	}

	listen(socket_serv, 5);
	char buffer[BUF_SIZE];
	while( socket_client = accept(socket_serv, NULL, NULL)) {
		printf("The connection is established \n");
		recv(socket_client, buffer, BUF_SIZE, 0);
		printf("Client: %s\n", buffer);
		send(socket_client, buffer, BUF_SIZE, 0);

	}
	
	close(socket_client);
	close(socket_serv);
	return 0;
}