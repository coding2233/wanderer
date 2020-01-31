#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <string.h>
#include <fcntl.h>

#define MAX_EVENTS 1024
#define SERVER_PORT 2233
#define BUFFER_MAX_SIZE 1024

int main()
{

    struct epoll_event ev, *events;

    int nfds;
    int conn_sock;

    unsigned char buffer[BUFFER_MAX_SIZE];

    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(struct sockaddr);
    //设置tcp 非阻塞模式 ，0: 为根据传输类型，选择对应的协议
    int lisenSocket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    //绑定
    bind(lisenSocket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(lisenSocket, 20);

    //创建epoll
    int epollfd = epoll_create(MAX_EVENTS);
    ev.events = EPOLLIN;
    ev.data.fd = lisenSocket;
    epoll_ctl(epollfd, EPOLL_CTL_ADD, lisenSocket, &ev);

    std::cout << " _____ ____   ___  _     _   " << std::endl;
    std::cout << "| ____|  _ \\ / _ \\| |   | |    " << std::endl;
    std::cout << "|  _| | |_) | | | | |   | |    " << std::endl;
    std::cout << "| |___|  __/| |_| | |___| |___ " << std::endl;
    std::cout << "|_____|_|    \\___/|_____|_____|" << std::endl;

    std::cout << "main hello world!!!" << std::endl;

    while (true)
    {
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);

        for (int i = 0; i < nfds; i++)
        {
            //监听连接的sock
            if (events[i].data.fd == lisenSocket)
            {
                conn_sock = accept(lisenSocket, (sockaddr *)&client_addr, &client_len);
                // fcntl(conn_sock,)
                ev.events = EPOLLIN | EPOLLOUT;
                ev.data.fd = conn_sock;
                epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev);
            }
            else
            {
                //读取
                if (events[i].events & EPOLLIN)
                {
                    auto size = recv(events[i].data.fd, buffer, BUFFER_MAX_SIZE, 0);
                    if (size > 0)
                    {
                        std::cout << buffer << std::endl;
                        /* code */
                    }
                }
                //发送
                else if (events[i].events & EPOLLOUT)
                {

                    /* code */
                }
            }
        }

        //    epoll_wait(epfd,event,)
    }

    return 0;
}
