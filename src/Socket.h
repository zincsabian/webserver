#ifndef SOCKET
#define SOCKET
#include "InetAddress.h"
class Socket{
private:
    int fd;
public:
    Socket();
    Socket(int);
    ~Socket();

    void listen();
    void bind(InetAddress* addr);
    void setnonbreaking();
    int accept(InetAddress* addr);
    int get_fd();
};
#endif