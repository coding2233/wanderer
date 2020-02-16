#include "network/network_module.h"
namespace wanderer
{
NetworkModule::NetworkModule()
{
}

NetworkModule::~NetworkModule()
{
}

void NetworkModule::OnInit()
{
    message_packer_ = new ProtobufMessagePacker;
    socket_ = new SocketEpoll;

    auto receiveCallback = std::bind(&NetworkModule::OnReceiveData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    auto connectCallback = std::bind(&NetworkModule::OnConnected, this, std::placeholders::_1);
    socket_->Setup(SERVER_PORT, connectCallback, receiveCallback);

    //message_packer_
}

void NetworkModule::OnUpdate()
{
    socket_->Loop();
}

void NetworkModule::OnClose()
{
    socket_->Close();
    delete socket_;
}

void NetworkModule::OnReceiveData(int fd, const char *data, int size)
{
    std::cout << "NetworkModule OnReceive Data" << fd << "  ##  " << data << "  ##  " << size << std::endl;
}

void NetworkModule::OnConnected(int fd)
{
    std::cout << "OnConnected: " << fd << std::endl;
    // sessions_iter_ = sessions_.find(fd);
    // if (sessions_iter_ == sessions_.end())
    // {
    //     Session *session = new Session;
    //     session->Setup(fd);
    //     sessions_.insert(std::make_pair(fd, session));
    // }
}

// void *CreateNetworkModule()
// {
//     return new NetworkModule();
// }
} // namespace wanderer