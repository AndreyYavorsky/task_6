#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define BUF_SIZE 512

int main(void)
{
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);

    SOCKET sock_server = socket(AF_INET, SOCK_DGRAM, 0);
  
    SOCKADDR_IN addr_server, addr_from;
    memset(&addr_server, 0, sizeof(addr_server));
    int from_len, length = sizeof(addr_server);

    addr_server.sin_family = AF_INET;
    addr_server.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &addr_server.sin_addr);


    char data[BUF_SIZE];
    char flag;
    while(1) {
        fgets(data, BUF_SIZE, stdin);
        sendto(sock_server, data, BUF_SIZE, 0,(struct sockaddr *)&addr_server, length);
        recvfrom(sock_server, data, BUF_SIZE, 0,(struct sockaddr *)&addr_from, &from_len);
        printf("Server: %s\n", data);
    }

    closesocket(sock_server );

    return 0;
}
