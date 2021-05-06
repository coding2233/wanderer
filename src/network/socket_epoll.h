#if unix

#ifndef __SOCKET_EPOLL_H__
#define __SOCKET_EPOLL_H__

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

#include "network/socket_base.h"
#include "utility/utility.h"

namespace wanderer
{

#define MAX_EVENTS 1024

    class SocketEpoll : public SocketBase
    {
    private:
        //服务端监听的socket
        int listen_socket_;
        //epoll的事件
        struct epoll_event ev_, *events_;
        //sock 地址
        struct sockaddr_in server_addr_, client_addr_;
        //客户端的长度
        socklen_t client_len_;
        //epoll instance
        int epoll_fd_;
        //有fd待处理数据的数目
        int nfds_;
        //连接的sock
        int conn_sock_;
        //等待时间
        int sleep_time_ = 0;
        //消息发送队列
        std::map<int, std::queue<std::string>> message_sending_queue_;
        //设置非阻塞模式
        int SetNonblocking(int sfd);
        //创建客户端段的socket
        void CreateClientSocket(const char name, const char *server_ip, int server_port, int sleep_time);

    public:
        SocketEpoll(/* args */);
        ~SocketEpoll();
        //设置
        virtual void Setup(std::function<void(int)> connected_callback, std::function<void(int, const char *data, int size)> receive_callback, std::function<void(const char name, int fd)> inner_connected_callback) override;
        //循环
        void Loop() override;
        //关闭
        void Close() override;
        //发送数据
        int SendData(int fd, const char *data, size_t size) override;
        //创建服务端监听socket
        int CreateListenSocket(const char *server_ip, int server_port) override;
        //创建客户端的socket
        void CreateConnectSocket(const char name, const char *server_ip, int server_port) override;

    protected:
        //设置logo
        void SetLogo() override;
    };

} // namespace wanderer
#endif

#endif