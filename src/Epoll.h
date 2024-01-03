#ifndef EPOLL_1
#define EPOLL_1
#include <vector>
class Epoll{
private:
    int epfd;
    std::vector<int> epoll_event;
public:
    Epoll();
    Epoll(int);
    ~Epoll()=default;
    void addFd(int,int);
    std::vector<int> poll();
};
#endif