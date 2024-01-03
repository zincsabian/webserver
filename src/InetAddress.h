#ifndef INETADDRESS
#define INETADDRESS
#include <string>
#include <arpa/inet.h>
class InetAddress{
public:
    sockaddr_in addr;
    socklen_t addr_len;
    InetAddress();
    InetAddress(std::string ip, uint16_t port);
    ~InetAddress() = default;
};
#endif