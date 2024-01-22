#ifndef SOCKET
#define SOCKET

class InetAddress;
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