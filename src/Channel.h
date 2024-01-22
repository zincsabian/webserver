#pragma once
// #include <sys/epoll.h>

class Epoll;
class Channel{
public:
    Channel() = default;
    void enableReading();
private:
    Epoll *ep;
    
};