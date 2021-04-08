#if unix

#include "network/socket_epoll.h"
namespace wanderer
{

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

    int SocketEpoll::SendData(int fd, const char *data, size_t size)
    {
        auto iter = message_sending_queue_.find(fd);
        if (iter == message_sending_queue_.end())
        {
            std::queue<std::string> msg_queue;
            message_sending_queue_.insert(std::make_pair(fd, msg_queue));
            iter = message_sending_queue_.find(fd);
        }
        iter->second.push(std::string(data, size));
        return 0;
        // return send(fd, data, size, 0);
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
    }

    void SocketEpoll::Setup(std::function<void(int)> connected_callback, std::function<void(int, const char *data, int size)> receive_callback, std::function<void(const char name, int fd)> inner_connected_callback)
    {
        SocketBase::Setup(connected_callback, receive_callback, inner_connected_callback);

        //创建epoll
        epoll_fd_ = epoll_create(MAX_EVENTS);

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
                epoll_event ev;
                ev.events = EPOLLIN | EPOLLOUT;
                ev.data.fd = conn_sock_;
                epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, conn_sock_, &ev);
                connected_callback_(conn_sock_);
            }
            else
            {
                //读取
                if (events_[i].events & EPOLLIN)
                {
                    auto size = recv(events_[i].data.fd, buffer_, BUFFER_MAX_SIZE, 0);
                    if (size > 0)
                    {
                        receive_callback_(events_[i].data.fd, buffer_, size);
                    }
                }
                //发送
                else if (events_[i].events & EPOLLOUT)
                {
                    /* code */
                    int fd = events_[i].data.fd;
                    auto iter = message_sending_queue_.find(fd);
                    if (iter != message_sending_queue_.end())
                    {
                        if (iter->second.size() > 0)
                        {
                            std::string send_message = iter->second.front();
                            iter->second.pop();
                            send(fd, send_message.c_str(), send_message.size(), 0);
                        }
                    }
                }
            }
        }
    }

    int SocketEpoll::CreateListenSocket(const char *server_ip, int server_port)
    {
        //设置tcp 非阻塞模式 ，0: 为根据传输类型，选择对应的协议
        listen_socket_ = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
        bzero(&server_addr_, sizeof(server_addr_));
        server_addr_.sin_family = AF_INET;
        server_addr_.sin_addr.s_addr = inet_addr(server_ip);
        server_addr_.sin_port = htons(server_port);

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

        ev_.events = EPOLLIN | EPOLLET;
        ev_.data.fd = listen_socket_;

        //添加 服务器的监听socket 到epoll中
        if (epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, listen_socket_, &ev_) < 0)
        {
            throw std::runtime_error("epoll ctrl error");
        }
        return listen_socket_;
    }

    void SocketEpoll::CreateConnectSocket(const char name, const char *server_ip, int server_port)
    {
        // int sleep_time(++sleep_time_);
        std::thread socket_thread(&SocketEpoll::CreateClientSocket, this, name, server_ip, server_port, sleep_time_);
        socket_thread.detach();
        // CreateClientSocket(name, server_ip, server_port, 0);
    }

    void SocketEpoll::CreateClientSocket(const char name, const char *server_ip, int server_port, int sleep_time)
    {
        sleep_time = 1.0;
        std::this_thread::sleep_for(std::chrono::seconds(sleep_time));

        int sock_client = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr, server_addr;
        bzero(&addr, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(0);
        if (bind(sock_client, (const sockaddr *)&addr, sizeof(addr)) < 0)
        {
            throw std::runtime_error("Inner socket bind error!");
        }
        //添加epoll中
        bzero(&server_addr, sizeof(server_addr));
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = inet_addr(server_ip);
        server_addr.sin_port = htons(server_port);
        int result = connect(sock_client, (const sockaddr *)&server_addr, sizeof(server_addr));
        if (result == 0)
        {
            //设置非阻塞模式
            int flag = fcntl(sock_client, F_GETFL, 0);
            fcntl(sock_client, F_SETFL, flag | O_NONBLOCK);
            //添加到epoll
            ev_.events = EPOLLIN | EPOLLOUT;
            ev_.data.fd = sock_client;
            epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, sock_client, &ev_);
            //回调
            inner_connected_callback_(name, sock_client);
        }
        else if (result < 0)
        {
            throw std::runtime_error("Innner socket connect server fail !");
        }
    }

    void SocketEpoll::Close()
    {
        shutdown(listen_socket_, SHUT_RD);
    }
} // namespace wanderer

#endif