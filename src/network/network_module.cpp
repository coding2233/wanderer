#include "network/network_module.h"
namespace wanderer
{

NetworkModule::NetworkModule(System *system) : Module(system)
{
    message_packer_ = new ProtobufMessagePacker;
#if WIN32
    throw std::runtime_error("IOCP not implemented yet!!");
#elif unix
    socket_ = new SocketEpoll;
#endif

    message_send_ = std::bind(&NetworkModule::OnMessageSend, this, std::placeholders::_1, std::placeholders::_2);
    message_receive_ = std::bind(&NetworkModule::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

    auto receive_callback = std::bind(&NetworkModule::OnReceiveData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    auto connect_callback = std::bind(&NetworkModule::OnConnected, this, std::placeholders::_1);
    auto inner_connected_callback = std::bind(&NetworkModule::OnInnerConnected, this, std::placeholders::_1, std::placeholders::_2);

    socket_->Setup(connect_callback, receive_callback, inner_connected_callback);
}

NetworkModule::~NetworkModule()
{
    delete message_packer_;
}

void NetworkModule::OnInit()
{
    // CreateServer("127.0.0.1", SERVER_PORT);
    //CreateInnerSession("ALL", "127.0.0.1", 2233);
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
    std::cout << "read receive data : " << fd << std::endl;
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
    std::cout << "connected to server:"
              << " [" << fd << "]" << std::endl;

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
}

void NetworkModule::CreateServer(const char *server_ip, int server_port)
{
    socket_->CreateListenSocket(server_ip, server_port);
    std::cout << "server runing: " << server_ip << ":" << server_port << std::endl;
}

void NetworkModule::CreateInnerSession(const char *name, const char *server_ip, int server_port)
{
    socket_->CreateConnectSocket(name, server_ip, server_port);
    std::cout << "inner session connecting: "
              << "[" << name << "] " << server_ip << ":" << server_port << std::endl;
}

void NetworkModule::OnInnerConnected(const char *name, int fd)
{
    sessions_iter_ = sessions_.find(fd);
    if (sessions_iter_ == sessions_.end())
    {
        Session *session = new Session;
        session->Setup(fd, message_send_, message_receive_);
        sessions_.insert(std::make_pair(fd, session));
        //内部的session
        inner_session_.insert(std::make_pair(name, session));
        S2G_RegisterInnerSession ss;
        ss.set_name(name);
        ss.set_secret("7c70519a56c6c16ab2c6be0c05c6455b");
        session->Send(ss);
        std::cout << "inner session connected:"
                  << " [" << name << "] "
                  << "[" << fd << "]" << std::endl;
    }
}

} // namespace wanderer