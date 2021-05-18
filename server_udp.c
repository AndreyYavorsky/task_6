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
	int sock_server;
	socklen_t client_len;
	char buffer[BUF_SIZE];
	int port = 9999;
	if (argc == 2) {
		port = atoi(argv[1]);
	}

	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	sock_server = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock_server < 0) {
		error("ERROR opening socket");
	}
	memset(&server_addr, 0, sizeof(server_addr));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(port);
	client_len = sizeof(client_addr);
	
	if (bind(sock_server, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		error("ERROR on binding");
	}

	while (1) {
		recvfrom(sock_server, buffer, BUF_SIZE, 0,(struct sockaddr *)&client_addr, &client_len);
		sendto(sock_server, buffer, BUF_SIZE, 0,(struct sockaddr *)&client_addr, client_len);
		printf("%s\n","Data sent ");
	}
	return 0;
}