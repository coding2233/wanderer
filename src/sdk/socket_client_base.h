#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__

#include <functional>
#include <iostream>

namespace wanderer
{

#define SOCKET_RECEIVE std::function<void(int, const char *data, int size)>

    class SocketClientBase
    {
    private:
        /* data */
    protected:
        SOCKET_RECEIVE receive_callback_;

    public:
        SocketClientBase(/* args */);
        ~SocketClientBase();

        virtual void Setup(SOCKET_RECEIVE receive_callback);

        virtual void Connect(const char *server_ip, int server_port) = 0;

        virtual void Receive(int socket, const char *data, size_t size) = 0;
    };
}
#endif