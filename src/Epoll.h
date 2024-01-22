#ifndef EPOLL_1
#define EPOLL_1
#include <vector>
#include <memory>
#include <sys/epoll.h>

class Channel;
class Epoll{
private:
    static int MAX_ENENTS;
    int epfd;
    epoll_event* epoll_events;
public:
    Epoll();
    ~Epoll();
    void addFd(int fd, uint32_t op);
    void updateChannel(Channel* channel);
    std::vector<epoll_event> poll(int time_out = -1);
};
#endif