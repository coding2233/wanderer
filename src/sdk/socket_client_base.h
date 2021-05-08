#ifndef __SOCKET_CLIENT_BASE_H__
#define __SOCKET_CLIENT_BASE_H__

#include <functional>
#include <iostream>
#include <cstring>
#include <vector>

#if WIN32
#include <WinSock2.h>
#elif __unix__ || __APPLE__
#include <sys/socket.h>
#endif


namespace wanderer
{

#define SOCKET_RECEIVE std::function<void(int, const char *data, int size)>
    // typedef void (*CONNECT_CALLBACK)(bool, int);
#define RECV_BUFFER_SIZE 1024

    class SocketClientBase
    {
    private:
        /* data */
    protected:
        SOCKET_RECEIVE receive_callback_;

        char *recv_buffer_;
        std::vector<int> sockets_;

    public:
        SocketClientBase(/* args */);
        virtual ~SocketClientBase();

        virtual void Update();

        virtual void Setup(SOCKET_RECEIVE receive_callback);

        virtual int SendData(int fd, const char* data, size_t size);

        virtual int Connect(const char *server_ip, int server_port) =0;

        virtual void Disconnect(int fd) =0;

    };
}
#endif