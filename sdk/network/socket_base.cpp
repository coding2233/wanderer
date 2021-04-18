#include "socket_base.h"
namespace wanderer
{
    SocketBase::SocketBase(/* args */)
    {
    }

    SocketBase::~SocketBase()
    {
    }

    void SocketBase::Setup(SOCKET_RECEIVE receive_callback)
    {
        receive_callback_ = receive_callback;
    }
}