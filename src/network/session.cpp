#include "network/session.h"

namespace wanderer
{

Session::Session(/* args */)
{
}

Session::~Session()
{
}

void Session::Setup(int fd, SocketBase *socket)
{
    fd_ = fd;
    socket_ = socket;
}

} // namespace wanderer