#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <map>

#if WIN32
#include "socket_windows.h"
#elif unix
#include "socket_unix.h"
#endif

#include "network/circle_buffer.h"

namespace wanderer
{
    class Network
    {
    private:
        /* data */
        SocketClientBase *socket_;

        std::map<int, CircleBuffer *> receive_buffer_;

    protected:
        virtual void OnReceive(int fd, const char *data, size_t size);

    public:
        Network(/* args */);
        ~Network();

        void Connect(const char *server_ip, int server_port, void *receive_callback, void *connect_faile);

        void DisConnect();

        void Send(int fd, const char *dta, size_t size);

        void Update();
    };
}

#endif