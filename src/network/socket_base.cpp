#include "network/socket_base.h"

namespace wanderer
{

SocketBase::SocketBase(/* args */)
{
}

SocketBase::~SocketBase()
{
}

void SocketBase::Setup(int port, std::function<void(int)> connectedCallback, std::function<void(int, const char *data, int size)> receiveCallback)
{
    connectedCallback_ = connectedCallback;
    receiveCallback_ = receiveCallback;
}

} // namespace wanderer