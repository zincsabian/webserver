#include "Channel.h"
#include "Epoll.h"

void Channel::enableReading()
{
    events = EPOLLIN;
    ep->updateChannel(this);
}

int Channel::getfd() { return fd; }

uint32_t Channel::getEvents() { return events; }

bool Channel::getInEpoll(){
    return inEpoll;
}
bool Channel::setInEpoll(){
    inEpoll = true;
}