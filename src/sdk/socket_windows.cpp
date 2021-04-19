#if WIN32

#include "socket_windows.h"

namespace wanderer
{
    SocketWindows::SocketWindows(/* args */)
    {
        // int BUF_SIZE = 1024;
        // WSADATA wsd;
        // SOCKET sHost;
        // SOCKADDR_IN servAddr; //服务器地址
        // int retVal;           //调用Socket函数的返回值
        // char buf[BUF_SIZE];
        // int iMode = 1;
        // //初始化Socket环境
        // if (WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
        // {
        //     printf("WSAStartup failed!\n");
        //     return;
        // }
        // sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        // //设置服务器Socket地址
        // servAddr.sin_family = AF_INET;
        // servAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
        // //在实际应用中，建议将服务器的IP地址和端口号保存在配置文件中
        // servAddr.sin_port = htons(9990);
        // //计算地址的长度
        // int sServerAddlen = sizeof(servAddr);
        // //调用ioctlsocket（）将其设置为非阻塞模式
        // retVal = ioctlsocket(sHost, FIONBIO, (u_long FAR *)&iMode);
        // if (retVal == SOCKET_ERROR)
        // {
        //     printf("ioctlsocket failed!");
        //     WSACleanup();
        //     return;
        // }

        // CreateThread(0, 0, WorkerThreadProc, (void *)this, 0, 0);
    }

    SocketWindows::~SocketWindows()
    {
    }

    void SocketWindows::Connect(const char *server_ip, int server_port)
    {
    }

    void SocketWindows::Receive(int socket, const char *data, size_t size)
    {
    }

    DWORD SocketWindows::WorkerThreadProc(LPVOID lpParam)
    {
        return 0;
    }

}
#endif