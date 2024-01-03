#include "Socket.h"
#include "util.h"
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
Socket::Socket(): fd(-1){
    fd = socket(AF_INET, SOCK_STREAM, 0);
    error_if(fd == -1, "socket create error");
}

Socket::Socket(int _fd): fd(_fd){
    error_if(fd == -1, "socket create error");
}

Socket::~Socket() {
    if(fd != -1) {
        close(fd);
        fd = -1;
    }
}

void Socket::listen() {
    error_if(::listen(fd, SOMAXCONN) == -1, "socket listen error");
}

void Socket::bind(std::shared_ptr<InetAddress> addr) {
    error_if(::bind(fd, (sockaddr*)&addr->addr, addr->addr_len) == -1, "socket bind error");
}

void Socket::setnonbreaking() {
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
}

int Socket::accept(std::shared_ptr<InetAddress> addr) {
    int client_sockfd = ::accept(fd, (sockaddr*)&addr->addr, &addr->addr_len);
    error_if(client_sockfd == -1, "socket accept error");
    return client_sockfd;
}

int Socket::get_fd() { return fd; }