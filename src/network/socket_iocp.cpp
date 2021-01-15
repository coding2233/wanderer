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

    void SocketIOCP::Setup(std::function<void(int)> connected_callback, std::function<void(int, const char *data, int size)> receive_callback, std::function<void(const char *name, int fd)> inner_connected_callback)
    {
        SocketBase::Setup(connected_callback, receive_callback, inner_connected_callback);
        ////create iocp
        //completion_port_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
        ////create worker thread
        //SYSTEM_INFO si;
        //GetSystemInfo(&si);
        //int worker_thread_num = si.dwNumberOfProcessors * 2;
        //HANDLE* worker_threads = new HANDLE[worker_thread_num];
        //for (int i = 0; i < worker_thread_num; i++)
        //{
        //    worker_threads[i] = CreateThread(0, 0, WorkerThreadProc, (void*)this, 0, 0);
        //}
        //logo
        SetLogo();
    }

    void SocketIOCP::Loop()
    {
    }

    void SocketIOCP::Close()
    {
    }
    int SocketIOCP::SendData(int fd, const char *data, size_t size)
    {
        return 0;
    }

    //创建服务端监听socket
    int SocketIOCP::CreateListenSocket(const char *server_ip, int server_port)
    {
        return 0;
    }

    //创建客户端的socket
    void SocketIOCP::CreateConnectSocket(const char *name, const char *server_ip, int server_port)
    {
    }
} // namespace wanderer
#endif