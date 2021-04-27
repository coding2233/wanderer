#if WIN32

#ifndef __SOCKET_WINDOWS_H__
#define __SOCKET_WINDOWS_H__

#include <windows.h>
#include <WinSock2.h>
#include <iostream>
#include <string>

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

        int Connect(const char *server_ip, int server_port) override;

        void Disconnect(int fd) override;
    };
}

#endif

#endif