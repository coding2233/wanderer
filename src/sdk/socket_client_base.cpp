#include "socket_client_base.h"
#include <iostream>
namespace wanderer
{
    SocketClientBase::SocketClientBase(/* args */)
    {
        std::cout<<"SocketClientBase::SocketClientBase"<<std::endl;
        recv_buffer_ = new char[RECV_BUFFER_SIZE];
    }

    SocketClientBase::~SocketClientBase()
    {
    }

    void SocketClientBase::Setup(SOCKET_RECEIVE receive_callback)
    {
        receive_callback_ = receive_callback;
        std::cout<<"SocketClientBase::Setup SOCKET_RECEIVE"<<std::endl;
    }


    void SocketClientBase::Update()
    {
        for (auto iter = sockets_.begin(); iter != sockets_.end(); iter++)
        {
            int recv_socket = *iter;
            memset(recv_buffer_, 0, RECV_BUFFER_SIZE);
            auto size = recv(recv_socket, recv_buffer_, RECV_BUFFER_SIZE, 0);
            if (size > 0)
            {
                receive_callback_(recv_socket, (const char*)recv_buffer_, size);
            }
        }
    }

    int SocketClientBase::SendData(int fd, const char* data, size_t size)
    {
        send(fd, data, size, 0);
        return 0;
    }

 
}