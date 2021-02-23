#if WIN32

#pragma once

#include <iostream>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include "network/socket_base.h"

#pragma comment(lib, "WS2_32.lib")

namespace wanderer
{
    // 释放指针的宏
    #define RELEASE(x)			{if(x != nullptr) {delete x; x = nullptr;}}
    // 释放句柄的宏
    #define RELEASE_HANDLE(x)	{if(x != NULL && x != INVALID_HANDLE_VALUE) { CloseHandle(x); x = INVALID_HANDLE_VALUE; }}
    // 释放Socket的宏
    #define RELEASE_SOCKET(x)	{if(x != INVALID_SOCKET) { closesocket(x); x = INVALID_SOCKET; }}

    class SocketIOCP : public SocketBase
    {
    private:
        //服务端监听的socket
        SOCKET listen_socket_;
        HANDLE completion_port_= INVALID_HANDLE_VALUE;
        HANDLE* worker_threads_=nullptr;

        static DWORD WINAPI WorkerThreadProc(LPVOID lpParam);
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