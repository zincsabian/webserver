#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <memory>
#include "util.h"
#include "Socket.h"
#include "InetAddress.h"
#include "Epoll.h"

void handle_read_event(int);

int main(int argc, char *argv[])
{
    Socket *server_sock = new Socket(); 
    InetAddress *server_addr = new InetAddress("127.0.0.1", 8888);
    server_sock->bind(server_addr);
    server_sock->listen();
    server_sock->setnonbreaking();

    Epoll* ep = new Epoll;
    ep->addFd(server_sock->get_fd(), EPOLLIN);

    while(true)
    {
        std::vector<epoll_event> events = ep->poll();
        for(epoll_event event: events)
        {
            if(event.data.fd == server_sock->get_fd()) //accept connection
            {
                InetAddress* client_addr = new InetAddress();
                Socket* client_sock = new Socket(server_sock->accept(client_addr));
                printf("new client fd %d! IP: %s Port: %d\n", client_sock->get_fd(), inet_ntoa(client_addr->addr.sin_addr), ntohs(client_addr->addr.sin_port));
                client_sock->setnonbreaking();
                ep->addFd(client_sock->get_fd(), EPOLLIN);
            } else if(event.events & EPOLLIN)
            {
                printf("rcv msg from fd: %d", event.data.fd);
                handle_read_event(event.data.fd);
            } else 
            {
                printf("something else happened\n");
            }
        }
    }
    delete server_sock;
    delete server_addr;
    delete ep;
    return 0;
}

void handle_read_event(int fd)
{
    const int BUFF_SIZE = 1024;
    char buffer[BUFF_SIZE];
    while(true)
    {
        memset(buffer, 0, sizeof(buffer));
        ssize_t read_bytes = read(fd, buffer, sizeof(buffer));
        if(read_bytes > 0)
        {
            printf("message from client fd %d: %s\n", fd, buffer);
            write(fd, buffer, sizeof(buffer));
        } else
        if(read_bytes == -1 && errno == EINTR)
        {  //客户端正常中断、继续读取
            printf("continue reading");
            continue;
        } else
        if(read_bytes == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
        {
            printf("finish reading once, errno: %d\n", errno);
            break;
        } else 
        if(read_bytes == 0)
        {
            printf("EOF, client fd %d disconnected\n", fd);
            close(fd);   //关闭socket会自动将文件描述符从epoll树上移除
            break;
        }
    }
}