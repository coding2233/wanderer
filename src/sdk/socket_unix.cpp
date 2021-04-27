#if unix
#include "socket_unix.h"

namespace wanderer
{
    SocketUnix::SocketUnix(/* args */)
    {
       /* std::thread socket_thread(&SocketUnix::ReceiveThread, this);
        socket_thread.detach();*/
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
        sockets_.push_back(connect_socket);
        return connect_socket;
    }

    void SocketUnix::Disconnect(int fd)
    {
        for (auto iter = sockets_.begin(); iter != sockets_.end(); iter++)
        {
            if (fd == *iter)
            {
                shutdown(fd, SHUT_RD);
                sockets_.erase(iter);
                break;
            }
        }
    }
}

#endif