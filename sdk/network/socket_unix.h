#if unix

#ifndef __SOCKET_UNIX_H__
#define __SOCKET_UNIX_H__

#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>

#include "socket_base.h"

namespace wanderer
{
    class SocketUnix : public SocketBase
    {
    private:
        /* data */
    public:
        SocketUnix(/* args */);
        ~SocketUnix();
    };
}

#endif

#endif