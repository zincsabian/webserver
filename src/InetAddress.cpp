#include "InetAddress.h"
#include <string>
#include <cstring>
InetAddress::InetAddress():addr_len(sizeof(addr)) {
    memset(&addr, 0, sizeof(addr));
}
InetAddress::InetAddress(std::string ip, uint16_t port):InetAddress(){
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    addr.sin_port = htons(port);
}