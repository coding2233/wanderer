#if WIN32

#ifndef __SOCKET_WINDOWS_H__
#define __SOCKET_WINDOWS_H__

#include "socket_base.h"
#include <WinSock2.h>
#include <windows.h>
#include <ws2tcpip.h>

#pragma comment(lib, "WS2_32.lib")

namespace wanderer
{
    class SocketWindows : public SocketBase
    {
    private:
        /* data */
        static DWORD WINAPI WorkerThreadProc(LPVOID lpParam);

    public:
        SocketWindows(/* args */);
        ~SocketWindows();
    };
}

#endif

#endif