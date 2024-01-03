#ifndef SOCKET
#define SOCKET
#include <memory>
#include "InetAddress.h"
class Socket{
private:
    int fd;
public:
    Socket();
    Socket(int);
    ~Socket() = default;

    //server
    void listen();
    void bind(std::shared_ptr<InetAddress> addr);
    void setnonbreaking();
    int accept(std::shared_ptr<InetAddress> addr);
    int get_fd();
};
#endif