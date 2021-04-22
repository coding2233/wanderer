#if unix
#include "socket_unix.h"

namespace wanderer
{
    SocketUnix::SocketUnix(/* args */)
    {
        std::thread socket_thread(&SocketUnix::ReceiveThread, this);
        socket_thread.detach();
    }

    SocketUnix::~SocketUnix()
    {
    }

    int SocketUnix::Connect(const char *server_ip, int server_port)
    {
        int connect_socket = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr, server_addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(0);
        if (bind(connect_socket, (const sockaddr *)&addr, sizeof(addr)) < 0)
        {
            throw std::runtime_error("Inner socket bind error!");
        }
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(server_ip);
        server_addr.sin_port = htons(server_port);
        int result = connect(connect_socket, (const sockaddr *)&server_addr, sizeof(server_addr));
        if (result == 0)
        {
            //设置非阻塞模式
            int flag = fcntl(connect_socket, F_GETFL, 0);
        }
        else if (result < 0)
        {
            throw std::runtime_error("Innner socket connect server fail !");
        }
        sockets_.insert(connect_socket);
        return connect_socket;
    }

    void SocketUnix::Disconnect(int fd)
    {
        for (auto iter = sockets_.begin(); iter != sockets_.end(); iter++)
        {
            if (fd == *iter)
            {
                close(fd);
                sockets_.erase(iter);
                break;
            }
        }
    }

    void SocketUnix::ReceiveThread()
    {
        int buffer_max = 1024;
        char *buffer = new char[buffer_max];
        while (true)
        {
            for (auto iter = sockets_.begin(); iter != sockets_.end(); iter++)
            {
                int recv_socket = *iter;
                auto size = recv(recv_socket, buffer, buffer_max, 0);
                if (size > 0)
                {
                    Receive(recv_socket, (const char *)buffer, size);
                }
            }
        }
        delete[] buffer;
    }

    int SocketUnix::SendData(int fd, const char *data, size_t size)
    {
        send(fd, data, size, 0);
        return 0;
    }

    void SocketUnix::Receive(int fd, const char *data, size_t size)
    {
        receive_callback_(fd, data, size);
    }

}

#endif