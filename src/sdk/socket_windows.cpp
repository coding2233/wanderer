#if WIN32

#include "socket_windows.h"

namespace wanderer
{
    SocketWindows::SocketWindows(/* args */)
    {
        WSADATA wsaData;
        // Initialize Winsock
        int wsa_startup_result = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (wsa_startup_result != 0) {
            throw std::runtime_error("WSAStartup failed: "+ std::to_string(wsa_startup_result));
        }

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
        WSACleanup();
    }

    int SocketWindows::Connect(const char *server_ip, int server_port)
    {
        SOCKET socket_client= socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (INVALID_SOCKET == socket_client)
        {
            throw std::runtime_error("Client socket creation failed.");
        }
        std::cout << "socket_client:" << socket_client << std::endl;
        sockaddr_in socket_addr;
        socket_addr.sin_family = AF_INET;
        socket_addr.sin_addr.S_un.S_addr = INADDR_ANY;
        socket_addr.sin_port = htons(0);
        if (bind(socket_client, (SOCKADDR*)&socket_addr, sizeof(SOCKADDR))== SOCKET_ERROR)
        {
            throw std::runtime_error("Client socket bind failed.");
        }
        std::cout << "socket_client Bind success!" << std::endl;
        //服务端的ip和地址
        sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.S_un.S_addr = inet_addr(server_ip);
        server_addr.sin_port = htons(server_port);
        int connect_result = connect(socket_client, (SOCKADDR*)&server_addr, sizeof(sockaddr_in));
        if (connect_result== SOCKET_ERROR)
        {
            throw std::runtime_error("Failed to connect to server. Server ip:"+ std::string(server_ip)+" port:"+std::to_string(server_port));
        }

        //设置非阻塞模式
        unsigned long ul = 1;
        int ret = ioctlsocket(socket_client, FIONBIO, (unsigned long*)&ul);
        if (ret == SOCKET_ERROR)
        {
            throw std::runtime_error("ioctlsocket error.");
        }
        sockets_.push_back((int)socket_client);
        return socket_client;
    }

    void SocketWindows::Disconnect(int fd)
    {
        for (auto iter = sockets_.begin(); iter != sockets_.end(); iter++)
        {
            if (fd == *iter)
            {
                closesocket(fd);
                sockets_.erase(iter);
                break;
            }
        }
    }




    //DWORD SocketWindows::WorkerThreadProc(LPVOID lpParam)
    //{
    //    return 0;
    //}

}
#endif