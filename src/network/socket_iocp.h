#if WIN32

#pragma once

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include "network/socket_base.h"

namespace wanderer
{
    class SocketIOCP : public SocketBase
    {
    private:
        HANDLE completion_port_;

    public:
        SocketIOCP();
        ~SocketIOCP();
        virtual void Setup(std::function<void(int)> connected_callback, std::function<void(int, const char *data, int size)> receive_callback, std::function<void(const char name, int fd)> inner_connected_callback) override;
        void Loop() override;
        void Close() override;
        int SendData(int fd, const char *data, size_t size) override;
        int CreateListenSocket(const char *server_ip, int server_port) override;
        void CreateConnectSocket(const char name, const char *server_ip, int server_port) override;

    protected:
        void SetLogo() override;
    };
} // namespace wanderer
#endif