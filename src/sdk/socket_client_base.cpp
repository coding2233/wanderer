#include "socket_client_base.h"
namespace wanderer
{
    SocketClientBase::SocketClientBase(/* args */)
    {
    }

    SocketClientBase::~SocketClientBase()
    {
    }

    void SocketClientBase::Setup(SOCKET_RECEIVE receive_callback)
    {
        receive_callback_ = receive_callback;
    }
}