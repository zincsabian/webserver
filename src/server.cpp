#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include "utils/error.h"

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error_if(sockfd == -1, "socket create error");

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);

    error_if(bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1, "socket bind error");
    error_if(listen(sockfd, SOMAXCONN) == -1, "socket listen error");

    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    bzero(&client_addr, sizeof(client_addr));

    int client_sockfd = accept(sockfd, (sockaddr*)&client_addr, &client_addr_len);

    printf("new client fd %d! IP: %s Port: %d\n", client_sockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    return 0;
}