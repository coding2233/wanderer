#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__

#include <functional>
#include <iostream>
#include <cstring>

#if WIN32
#include <WinSock2.h>
#elif unix
#include <sys/socket.h>
#endif

namespace wanderer
{

#define SOCKET_RECEIVE std::function<void(int, const char *data, int size)>
#define CONNECT_CALLBACK std::function<void(bool, int)>
    // typedef void (*CONNECT_CALLBACK)(bool, int);
#define RECV_BUFFER_SIZE 1024

    class SocketClientBase
    {
    private:
        /* data */
    protected:
        SOCKET_RECEIVE receive_callback_;

        char recv_buffer_[RECV_BUFFER_SIZE];
        std::vector<int> sockets_;

    public:
        SocketClientBase(/* args */);
        ~SocketClientBase();

        virtual void Update();

        virtual void Setup(SOCKET_RECEIVE receive_callback);

        virtual int SendData(int fd, const char* data, size_t size);

        virtual int Connect(const char *server_ip, int server_port) = 0;

        virtual void Disconnect(int fd) = 0;

    };
}
#endif