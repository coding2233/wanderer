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
    auto callBack = std::bind(&NetworkModule::OnReceiveData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    socket_epoll_->Setup(SERVER_PORT, callBack);
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

void NetworkModule::OnReceiveData(int fd, unsigned char *data, int size)
{
    std::cout << "NetworkModule OnReceive Data" << fd << "  ##  " << data << "  ##  " << size << std::endl;
}

// void *CreateNetworkModule()
// {
//     return new NetworkModule();
// }