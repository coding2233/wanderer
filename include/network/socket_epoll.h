#ifndef __EPOLLSOCKET_H__
#define __EPOLLSOCKET_H__

#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <string.h>

#define MAX_EVENTS 1024
#define BUFFER_MAX_SIZE 1024

class SocketEpoll
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
    //缓存数据
    unsigned char buffer_[BUFFER_MAX_SIZE];

private:
    //设置非阻塞模式
    int SetNonblocking(int sfd);
    //设置logo
    void SetLogo();

public:
    SocketEpoll(/* args */);
    ~SocketEpoll();
    //设置
    void Setup(int port);
    //循环
    void Loop();
    //关闭
    void Close();
};

#endif