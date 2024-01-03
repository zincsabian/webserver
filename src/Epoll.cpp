#include "Epoll.h"
#include "util.h"
#include <sys/epoll.h>
Epoll::Epoll():epfd(-1){
    epfd = epoll_create1(0);
    error_if(epfd == -1, "epoll fd create error");
}
Epoll::Epoll(int fd):epfd(fd){
    error_if(epfd == -1, "epoll fd create error");
}