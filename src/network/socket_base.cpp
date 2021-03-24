#include "network/socket_base.h"

namespace wanderer
{

    SocketBase::SocketBase(/* args */)
    {
    }

    SocketBase::~SocketBase()
    {
    }

    void SocketBase::Setup(std::function<void(int)> connected_callback, std::function<void(int, const char *data, int size)> receive_callback, std::function<void(const char name, int fd)> inner_connected_callback)
    {
        connected_callback_ = connected_callback;
        receive_callback_ = receive_callback;
        inner_connected_callback_ = inner_connected_callback;
    }

    int SocketBase::CreateListenSocket(const char *server_ip, int server_port)
    {
        return 0;
    }
    void SocketBase::CreateConnectSocket(const char name, const char *server_ip, int server_port)
    {
    }

} // namespace wanderer