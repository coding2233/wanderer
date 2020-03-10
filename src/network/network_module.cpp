#include "network/network_module.h"
namespace wanderer
{

NetworkModule::NetworkModule()
{
    message_send_ = std::bind(&NetworkModule::OnMessageSend, this, std::placeholders::_1, std::placeholders::_2);
    message_receive_ = std::bind(&NetworkModule::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
}

NetworkModule::~NetworkModule()
{
}

void NetworkModule::OnInit()
{
    message_packer_ = new ProtobufMessagePacker;

#if WIN32
    throw std::runtime_error("IOCP not implemented yet!!");
#elif unix
    socket_ = new SocketEpoll;
#endif

    auto receiveCallback = std::bind(&NetworkModule::OnReceiveData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    auto connectCallback = std::bind(&NetworkModule::OnConnected, this, std::placeholders::_1);
    socket_->Setup(connectCallback, receiveCallback);

    CreateServer(SERVER_PORT);
    CreateInnerSession("ALL", "127.0.0.1", 2233);
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
    sessions_iter_ = sessions_.find(fd);
    if (sessions_iter_ != sessions_.end())
    {
        sessions_iter_->second->Receive(data, size);
    }
    else
    {
        throw std::runtime_error("can't find session: " + fd);
    }
}

void NetworkModule::OnConnected(int fd)
{
    std::cout << "OnConnected: " << fd << std::endl;
    sessions_iter_ = sessions_.find(fd);
    if (sessions_iter_ == sessions_.end())
    {
        Session *session = new Session;
        session->Setup(fd, message_send_, message_receive_);
        sessions_.insert(std::make_pair(fd, session));
    }
}

void NetworkModule::OnMessageSend(int fd, const google::protobuf::Message &message)
{
    size_t size = message_packer_->ToBytes(message);
    socket_->SendData(fd, message_packer_->Read(), size);
}

void NetworkModule::OnMessageReceive(const Session *session, int type, const char *data, int size)
{
    message_packer_->Dispatcher(session, type, data, size);
    // dispatcher_->Dispatcher(session, type, data, size);
}

void NetworkModule::CreateServer(int server_port)
{
    socket_->CreateListenSocket(server_port);
}

void NetworkModule::CreateInnerSession(const char *name, const char *server_ip, int server_port)
{
    int fd = socket_->CreateConnectSocket(server_ip, server_port);
    sessions_iter_ = sessions_.find(fd);
    if (sessions_iter_ != sessions_.end())
    {
        inner_session_.insert(std::make_pair(name, sessions_iter_->second));
    }
}

// void *CreateNetworkModule()
// {
//     return new NetworkModule();
// }
} // namespace wanderer