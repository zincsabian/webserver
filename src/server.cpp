#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>

int main()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr));
    listen(sockfd, SOMAXCONN);

    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    bzero(&client_addr, sizeof(client_addr));

    int client_sockfd = accept(sockfd, (sockaddr*)&client_addr, &client_addr_len);

    printf("new client fd %d! IP: %s Port: %d\n", client_sockfd, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    return 0;
}