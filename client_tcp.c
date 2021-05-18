#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUF_SIZE 512

int main(void)
{
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);

    SOCKET my_socket;
    my_socket = socket(AF_INET, SOCK_STREAM, 0);

    SOCKADDR_IN addr_server;
    memset(&addr_server, 0, sizeof(addr_server));

    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(1313);
    inet_pton(AF_INET, "127.0.0.1", &addr_server.sin_addr);

    connect(my_socket, (SOCKADDR*) &addr_server, sizeof(addr_server));

    char data[BUF_SIZE];
    fgets(data, BUF_SIZE, stdin);
    send(my_socket, data, BUF_SIZE, 0);
    recv(my_socket, data, BUF_SIZE, 0);
    printf("Server: %s\n", data);
    closesocket(my_socket);

    return 0;
}
