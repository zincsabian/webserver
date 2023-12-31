#include "Epoll.h"
#include "util.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <cstring>
#include <fcntl.h>

int Epoll::MAX_ENENTS = 1024;

Epoll::Epoll() : epfd(-1)
{
    epfd = epoll_create1(0);
    error_if(epfd == -1, "epoll fd create error");
    epoll_events = new epoll_event[MAX_ENENTS];
    std::memset(epoll_events, 0, sizeof(epoll_event) * MAX_ENENTS);
}

Epoll::~Epoll() 
{
    if(epfd != -1) 
    {
        close(epfd);
        delete[] epoll_events;
        epfd = -1;
    }
}

void Epoll::addFd(int fd, uint32_t op) 
{
    epoll_event ev;
    memset(&ev, 0, sizeof(ev));
    ev.events = op; //using LT model
    ev.data.fd = fd;
    ssize_t status = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev);
    error_if(status == -1, "epoll add event error");
}

std::vector<epoll_event> Epoll::poll(int timeout) 
{
    int nfds = epoll_wait(epfd, epoll_events, MAX_ENENTS, timeout);
    error_if(nfds == -1, "epoll wait error");
    std::vector<epoll_event> atvfd;
    for(int i = 0; i < nfds; i++) 
    {
        atvfd.push_back(epoll_events[i]);
    }
    return atvfd;
}