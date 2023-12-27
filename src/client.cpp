#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
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
        
    }
}