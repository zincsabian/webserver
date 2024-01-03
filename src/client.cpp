#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <memory>
#include <unistd.h>
#include "util.h"
#include "InetAddress.h"

int main(int argc, char *argv[])
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0); 

    std::shared_ptr<InetAddress> client_addr = std::make_shared<InetAddress>("127.0.0.1", 8888);
    // std::shared_ptr<InetAddress> addr2 = std::make_shared<InetAddress>();
    // connect(sockfd, (sockaddr*)&client_addr, sizeof(client_addr));

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