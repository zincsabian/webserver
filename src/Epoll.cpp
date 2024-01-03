#include "Epoll.h"
#include "util.h"
#include <sys/epoll.h>
#include <unistd.h>

Epoll::Epoll():epfd(-1){
    epfd = epoll_create1(0);
    error_if(epfd == -1, "epoll fd create error");
    std::vector<epoll_event>().swap(epoll_events);
}

Epoll::~Epoll() {
    if(epfd != -1) {
        close(epfd);
        epfd = -1;
    }
    std::vector<epoll_event>().swap(epoll_events);
}

void Epoll::addFd(int Fd, uint32_t op) {
    // error_if()
}