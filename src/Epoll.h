#ifndef EPOLL_1
#define EPOLL_1
#include <vector>
#include <sys/epoll.h>
class Epoll{
private:
    static int MAX_ENENTS;
    int epfd;
    std::vector<epoll_event> epoll_events;
public:
    Epoll();
    ~Epoll();
    void addFd(int fd,uint32_t op);
    std::vector<epoll_event> poll(int time_out = -1);
};
#endif