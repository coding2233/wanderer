#include "network/network_module.h"

NetworkModule::NetworkModule(/* args */)
{
}

NetworkModule::~NetworkModule()
{
}

void NetworkModule::OnInit()
{
    socket_epoll_ = new SocketEpoll;
    socket_epoll_->Setup(SERVER_PORT);
}

void NetworkModule::OnUpdate()
{
    socket_epoll_->Loop();
}

void NetworkModule::OnClose()
{
    socket_epoll_->Close();
    delete socket_epoll_;
}