#ifndef __SOCKET_INNER_LINUX_H__
#define __SOCKET_INNER_LINUX_H__

#include <sys/socket.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <iostream>
#include <functional>
#include <arpa/inet.h>
#include <string.h>

namespace wanderer
{

#define BUFFER_MAX_SIZE 1024

class SocketInnerLinux
{
private:
    /* data */
    int socket_client_;
    //缓存数据
    char buffer_[BUFFER_MAX_SIZE];
    //接收回调
    std::function<void(int, const char *data, int size)> receiveCallback_;

public:
    SocketInnerLinux(/* args */);
    ~SocketInnerLinux();

    int GetSocket();

    void Setup(const char *server_ip, int server_port, std::function<void(int, const char *data, int size)> receiveCallback);

    void Loop();

    void Close();

    int SendData(const char *data, size_t size);
};
} // namespace wanderer

#endif