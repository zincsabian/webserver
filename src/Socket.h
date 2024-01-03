#ifndef SOCKET
#define SOCKET
#include "InetAddress.h"
#include <memory>
class Socket{
private:
    int fd;
public:
    Socket();
    Socket(int);
    ~Socket();

    void listen();
    void bind(std::shared_ptr<InetAddress> addr);
    void setnonbreaking();
    int accept(std::shared_ptr<InetAddress> addr);
    int get_fd();
};
#endif