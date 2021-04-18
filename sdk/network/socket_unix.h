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
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <thread>

#include "socket_base.h"

namespace wanderer
{
    class SocketUnix : public SocketBase
    {
    private:
        /* data */
        int socket_login_;

    public:
        SocketUnix(/* args */);
        ~SocketUnix();

        void Connect(const char *server_ip, int server_port) override;

        void Receive(int socket, const char *data, size_t size) override;

        void ReceiveThread();
    };
}

#endif

#endif