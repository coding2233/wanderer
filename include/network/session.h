#ifndef __SESSION_H__
#define __SESSION_H__

#include "network/socket_base.h"
#include "network/message_packer.h"

namespace wanderer
{

class Session
{
private:
    /* data */
    int fd_;
    SocketBase *socket_;

public:
    Session(/* args */);
    ~Session();

    void Setup(int fd, SocketBase *socket);
};

} // namespace wanderer

#endif