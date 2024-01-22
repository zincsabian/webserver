#pragma once
#include <sys/epoll.h>

class Epoll;
class Channel{
public:
    Channel() = default;
    Channel(Epoll *ep, int fd);
    int getfd();
    void enableReading();
    uint32_t getEvents();
    bool getInEpoll();
    void setInEpoll();
private:
    Epoll *ep;
    int fd;
    uint32_t events;
    uint32_t revents;
    bool inEpoll;
};