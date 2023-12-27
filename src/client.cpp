#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <unistd.h>
#include "utils/error.h"

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    //ipv4, tcp
    // int sock = socket(AF_INET6, SOCK_DGRAM, 0); //ipv6, udp
    sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    client_addr.sin_port = htons(8888);

    connect(sockfd, (sockaddr*)&client_addr, sizeof(client_addr));

    while(true)
    {
        const int BUFSIZE = 1024;
        char buffer[BUFSIZE];
        memset(buffer, 0, sizeof(buffer));
        fgets(buffer, BUFSIZE, stdin); // protect, avoid buffer overflow
        ssize_t write_bytes = write(sockfd, buffer, sizeof(buffer));
        if(write_bytes == -1) {
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        memset(buffer, 0, sizeof(buffer));
        ssize_t read_bytes = read(sockfd, buffer, sizeof(buffer));
        if(read_bytes > 0) {
            printf("message from server: %s\n", buffer);
        }else if(read_bytes == 0){      //read返回0，表示EOF，通常是服务器断开链接，等会儿进行测试
            printf("server socket disconnected!\n");
            break;
        }else if(read_bytes == -1){     //read返回-1，表示发生错误，按照上文方法进行错误处理
            close(sockfd);
            error_if(true, "socket read error");
        }
    }
}