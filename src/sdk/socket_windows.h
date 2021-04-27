#if WIN32

#ifndef __SOCKET_WINDOWS_H__
#define __SOCKET_WINDOWS_H__

#include <windows.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

#include "socket_client_base.h"

namespace wanderer
{
    class SocketWindows : public SocketClientBase
    {
    private:
        /* data */
        //static DWORD WINAPI WorkerThreadProc(LPVOID lpParam);

    public:
        SocketWindows(/* args */);
        ~SocketWindows();

        void Update() override;

        int Connect(const char *server_ip, int server_port) override;

        void Disconnect(int fd) override;

        void Receive(int socket, const char *data, size_t size) override;

        int SendData(int fd, const char *data, size_t size) override;
    };
}

#endif

#endif