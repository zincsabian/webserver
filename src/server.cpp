#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "utils/error.h"

void setnonblocking(int fd){
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int main(int argc, char *argv[])
{
    // return 0;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    error_if(sockfd == -1, "socket create error");

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(8888);

    error_if(bind(sockfd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1, "socket bind error");
    error_if(listen(sockfd, SOMAXCONN) == -1, "socket listen error");

    //using epoll to 
    int epfd = epoll_create1(0);
    error_if(epfd == -1, "epoll create error");
    const int MAX_ENENTS = 1024;
    epoll_event events[MAX_ENENTS], ev;
    memset(events, 0, sizeof(events));
    memset(&ev, 0, sizeof(ev));

    ev.events = EPOLLIN; //using LT model
    ev.data.fd = sockfd;
    setnonblocking(sockfd);
    epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);

    while(true)
    {
        int nfds = epoll_wait(epfd, events, MAX_ENENTS, -1);
        error_if(nfds == -1, "epoll wait error");
        for(int i = 0; i < nfds; i++)
        {
            if(events[i].data.fd == sockfd) //accept connection
            {
                sockaddr_in client_addr;
                memset(&client_addr, 0, sizeof(client_addr));
                socklen_t client_addr_len = sizeof(client_addr);
                int client_sockfd = accept(sockfd, (sockaddr*)&client_sockfd, &client_addr_len);
                error_if(client_sockfd == -1, "socket accept error");
                printf("new client fd %d! IP: %s Port: %d\n", client_addr, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
          
                memset(&ev, 0, sizeof(ev));
                ev.data.fd = client_sockfd;
                ev.events = EPOLLIN;
                setnonblocking(client_sockfd);
                epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ev);
            } else if(events[i].events & EPOLLIN)
            {
                const int BUFSIZE = 1024;
                char buffer[BUFSIZE];
                while(true)
                {
                    memset(&buffer, 0, sizeof(buffer));
                    ssize_t byte_read = read(events[i].data.fd, buffer, sizeof(buffer));
                    if(byte_read > 0) 
                    {
                        printf("message from client fd %d: %s\n", events[i].data.fd, buffer);
                        write(events[i].data.fd, buffer, sizeof(buffer));
                    } else
                    if(byte_read == -1 && errno == EINTR)
                    {
                        printf("continue reading");
                        continue;
                    } else
                    if(byte_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
                    {
                        printf("finish reading once, errno: %d\n", errno);
                        break;
                    } else
                    if(byte_read == 0)
                    {
                        printf("EOF, client fd %d disconnected\n", events[i].data.fd);
                        close(events[i].data.fd);   //关闭socket会自动将文件描述符从epoll树上移除
                        break;
                    }
                }
            }
        }
    }
}