#include "network/socket_epoll.h"

SocketEpoll::SocketEpoll(/* args */)
{
    //地址长度
    client_len_ = sizeof(struct sockaddr);
    //事件
    events_ = new epoll_event[MAX_EVENTS];
}

SocketEpoll::~SocketEpoll()
{
    delete[] events_;
}

void SocketEpoll::SetLogo()
{
    std::cout << "**"
              << "*******************************"
              << "**" << std::endl;
    std::cout << "**"
              << " _____ ____   ___  _     _     "
              << "**" << std::endl;
    std::cout << "**"
              << "| ____|  _ \\ / _ \\| |   | |    "
              << "**" << std::endl;
    std::cout << "**"
              << "|  _| | |_) | | | | |   | |    "
              << "**" << std::endl;
    std::cout << "**"
              << "| |___|  __/| |_| | |___| |___ "
              << "**" << std::endl;
    std::cout << "**"
              << "|_____|_|    \\___/|_____|_____|"
              << "**" << std::endl;
    std::cout << "**"
              << "*******************************"
              << "**" << std::endl;

    std::cout << "server runing ..." << std::endl;
}

void SocketEpoll::Setup(int port, std::function<void(int, unsigned char *data, int size)> callback)
{
    callback_ = callback;

    //设置tcp 非阻塞模式 ，0: 为根据传输类型，选择对应的协议
    listen_socket_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    bzero(&server_addr_, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr_.sin_port = htons(port);

    //绑定
    if (bind(listen_socket_, (struct sockaddr *)&server_addr_, sizeof(server_addr_)) < 0)
    {
        throw std::runtime_error("lisenSocket bind error");
    }
    //监听
    if (listen(listen_socket_, 20) < 0)
    {
        throw std::runtime_error("lisenSocket listen error");
    }

    //创建epoll
    epoll_fd_ = epoll_create(MAX_EVENTS);
    ev_.events = EPOLLIN | EPOLLET;
    ev_.data.fd = listen_socket_;

    //添加 服务器的监听socket 到epoll中
    if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, listen_socket_, &ev_) < 0)
    {
        throw std::runtime_error("epoll ctrl error");
    }

    //设置logo
    SetLogo();
}

void SocketEpoll::Loop()
{
    nfds_ = epoll_wait(epoll_fd_, events_, MAX_EVENTS, -1);
    if (nfds_ == -1)
    {
        throw std::runtime_error("epoll wait error :-1");
    }

    for (int i = 0; i < nfds_; i++)
    {
        //监听连接的sock
        if (events_[i].data.fd == listen_socket_)
        {
            conn_sock_ = accept(listen_socket_, (sockaddr *)&client_addr_, &client_len_);
            // fcntl(conn_sock,)
            ev_.events = EPOLLIN | EPOLLOUT;
            ev_.data.fd = conn_sock_;
            epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, conn_sock_, &ev_);
        }
        else
        {
            //读取
            if (events_[i].events & EPOLLIN)
            {
                auto size = recv(events_[i].data.fd, buffer_, BUFFER_MAX_SIZE, 0);
                if (size > 0)
                {
                    std::cout
                        << buffer_ << std::endl;
                    callback_(events_[i].data.fd, buffer_, size);

                    //          send(events_[i].data.fd, buffer_, size, 0);
                    /* code */
                }
            }
            // //发送
            // else if (events_[i].events & EPOLLOUT)
            // {
            //     /* code */
            // }
        }
    }
}

void SocketEpoll::Close()
{
    shutdown(listen_socket_, SHUT_RD);
}