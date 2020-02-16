#ifndef __SOCKET_EPOLL_H__
#define __SOCKET_EPOLL_H__

#include "network/socket_base.h"

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>

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

private:
    //设置非阻塞模式
    int SetNonblocking(int sfd);

public:
    SocketEpoll(/* args */);
    ~SocketEpoll();
    //设置
    virtual void Setup(int port, std::function<void(int)> connectedCallback, std::function<void(int, const char *data, int size)> receiveCallback) override;
    //循环
    void Loop() override;
    //关闭
    void Close() override;
    //发送数据
    int SendData(int fd, const char *data, size_t size) override;

protected:
    //设置logo
    void SetLogo() override;
};

} // namespace wanderer
#endif