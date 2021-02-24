#if WIN32

#include "network/socket_iocp.h"

namespace wanderer
{
    SocketIOCP::SocketIOCP()
    {
    }

    SocketIOCP::~SocketIOCP()
    {
    }
    //https://www.cnblogs.com/tanguoying/p/8439701.html
    void SocketIOCP::SetLogo()
    {
        std::cout << "***********************************" << std::endl;
        std::cout << "**  ___    ___     ____   ____   **" << std::endl;
        std::cout << "** |_ _|  / _ \\   / ___| |  _ \\  **" << std::endl;
        std::cout << "**  | |  | | | | | |     | |_) | **" << std::endl;
        std::cout << "**  | |  | |_| | | |___  |  __/  **" << std::endl;
        std::cout << "** |___|  \\___/   \\____| |_|     **" << std::endl;
        std::cout << "**                               **" << std::endl;
        std::cout << "***********************************" << std::endl;
    }

    void SocketIOCP::Setup(std::function<void(int)> connected_callback, std::function<void(int, const char *data, int size)> receive_callback, std::function<void(const char name, int fd)> inner_connected_callback)
    {
        SocketBase::Setup(connected_callback, receive_callback, inner_connected_callback);
        //create iocp
        completion_port_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
        //create worker thread. Twice the number of cores.
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        int worker_thread_num = si.dwNumberOfProcessors * 2;
        worker_threads_ = new HANDLE[worker_thread_num];
        for (int i = 0; i < worker_thread_num; i++)
        {
            worker_threads_[i] = CreateThread(0, 0, WorkerThreadProc, (void*)this, 0, 0);
        }
        //logo
        SetLogo();
    }

    void SocketIOCP::Loop()
    {
    }

    void SocketIOCP::Close()
    {
        RELEASE_HANDLE(completion_port_);
        RELEASE(worker_threads_);
        RELEASE_SOCKET(listen_socket_);
    }

    int SocketIOCP::SendData(int fd, const char *data, size_t size)
    {
        return 0;
    }

    //创建服务端监听socket
    int SocketIOCP::CreateListenSocket(const char *server_ip, int server_port)
    {
        listen_socket_=WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
        if (INVALID_SOCKET== listen_socket_)
        {
            throw std::runtime_error("Listening for socket invalid.");
        }

        // 将socket绑定到完成端口中
        if (NULL == CreateIoCompletionPort((HANDLE)listen_socket_, completion_port_, (DWORD)listen_socket_, 0))
        {
            RELEASE_SOCKET(listen_socket_);
            return false;
        }

        //服务器地址信息，用于绑定socket
        sockaddr_in serverAddr;

        // 填充地址信息
        ZeroMemory((char*)&serverAddr, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(server_ip);
        serverAddr.sin_port = htons(server_port);

        // 绑定地址和端口
        if (SOCKET_ERROR == bind(listen_socket_, (sockaddr*)&serverAddr, sizeof(serverAddr)))
        {
            throw std::runtime_error("Failed to listen for socket binding. ");
        }

        // 监听
        if (SOCKET_ERROR == listen(listen_socket_, SOMAXCONN))
        {
            throw std::runtime_error("LisenSocket listen error.");
        }

        return listen_socket_;
    }

    //创建客户端的socket
    void SocketIOCP::CreateConnectSocket(const char name, const char *server_ip, int server_port)
    {
    }

    DWORD SocketIOCP::WorkerThreadProc(LPVOID lpParam)
    {
        SocketIOCP *iocp= (SocketIOCP*)lpParam;
        DWORD dw_bytes = 0;
        SOCKET *socket;
        OVERLAPPED* ol = NULL;
        while (true)
        {
            bool result = GetQueuedCompletionStatus(iocp->completion_port_, &dw_bytes, (PULONG_PTR)&socket, &ol, NULL);
        }
        return 0;
    }

} // namespace wanderer
#endif