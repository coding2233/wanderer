#if unix


#ifndef __SOCKET_UNIX_H__
#define __SOCKET_UNIX_H__


#include <arpa/inet.h>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <netinet/in.h>
#include <queue>
#include <sys/epoll.h>
#include <sys/socket.h>
// #include <thread>

#include "socket_client_base.h"

namespace wanderer
{
    class SocketUnix : public SocketClientBase
    {
    private:
        /* data */
    public:
        SocketUnix(/* args */);
        ~SocketUnix();

        virtual int Connect(const char *server_ip, int server_port) override;

        void Disconnect(int fd) override;

        //void ReceiveThread();
    };
}

#endif

#endif