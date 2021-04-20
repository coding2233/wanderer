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

    void SocketUnix::Connect(const char *server_ip, int server_port)
    {
        socket_login_ = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr, server_addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(0);
        if (bind(socket_login_, (const sockaddr *)&addr, sizeof(addr)) < 0)
        {
            throw std::runtime_error("Inner socket bind error!");
        }
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(server_ip);
        server_addr.sin_port = htons(server_port);
        int result = connect(socket_login_, (const sockaddr *)&server_addr, sizeof(server_addr));
        if (result == 0)
        {
            //设置非阻塞模式
            int flag = fcntl(socket_login_, F_GETFL, 0);
        }
        else if (result < 0)
        {
            throw std::runtime_error("Innner socket connect server fail !");
        }
    }

    void SocketUnix::ReceiveThread()
    {
        int buffer_max = 1024;
        char *buffer = new char[buffer_max];
        while (true)
        {
            if (socket_login_ > 0)
            {
                auto size = recv(socket_login_, buffer, buffer_max, 0);
                if (size > 0)
                {
                    Receive(socket_login_, (const char *)buffer, size);
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