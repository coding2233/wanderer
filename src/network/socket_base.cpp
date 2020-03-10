#include "network/socket_base.h"

namespace wanderer
{

SocketBase::SocketBase(/* args */)
{
}

SocketBase::~SocketBase()
{
}

void SocketBase::Setup(std::function<void(int)> connectedCallback, std::function<void(int, const char *data, int size)> receiveCallback)
{
    connectedCallback_ = connectedCallback;
    receiveCallback_ = receiveCallback;
}

int SocketBase::CreateListenSocket(int server_port)
{
}
int SocketBase::CreateConnectSocket(const char *server_ip, int server_port)
{
}

} // namespace wanderer