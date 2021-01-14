#if WIN32

#pragma once

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>

#include "network/socket_base.h"


namespace wanderer
{
    class SocketIOCP : public SocketBase
    {
    public:
        SocketIOCP();
        ~SocketIOCP();
        //设置
        virtual void Setup(std::function<void(int)> connected_callback, std::function<void(int, const char* data, int size)> receive_callback, std::function<void(const char* name, int fd)> inner_connected_callback) override;
        //循环
        void Loop() override;
        //关闭
        void Close() override;
        //发送数据
        int SendData(int fd, const char* data, size_t size) override;
        //创建服务端监听socket
        int CreateListenSocket(const char* server_ip, int server_port) override;
        //创建客户端的socket
        void CreateConnectSocket(const char* name, const char* server_ip, int server_port) override;

    protected:
        //设置logo
        void SetLogo() override;
    };
}
#endif