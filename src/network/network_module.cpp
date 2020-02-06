#include "network/network_module.h"

NetworkModule::NetworkModule()
{
}

NetworkModule::~NetworkModule()
{
}

void NetworkModule::OnInit()
{
    socket_epoll_ = new SocketEpoll;
    socket_epoll_->Setup(SERVER_PORT);

    // app_->GetModule("network");
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

// void *CreateNetworkModule()
// {
//     return new NetworkModule();
// }