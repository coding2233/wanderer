#include "network/network_module.h"
namespace wanderer
{

    NetworkModule::NetworkModule(System *system) : Module(system)
    {
        //message_packer_ = new ProtobufMessagePacker;
#if WIN32
        //throw std::runtime_error("IOCP not implemented yet!!");
        socket_ = new SocketIOCP;
#elif unix
        socket_ = new SocketEpoll;
#endif

        message_send_ = std::bind(&NetworkModule::OnMessageSend, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        message_receive_ = std::bind(&NetworkModule::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2);

        auto receive_callback = std::bind(&NetworkModule::OnReceiveData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        auto connect_callback = std::bind(&NetworkModule::OnConnected, this, std::placeholders::_1);
        auto inner_connected_callback = std::bind(&NetworkModule::OnInnerConnected, this, std::placeholders::_1, std::placeholders::_2);

        socket_->Setup(connect_callback, receive_callback, inner_connected_callback);
    }

    NetworkModule::~NetworkModule()
    {
        //delete message_packer_;
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
        LOG(INFO) << "OnReceiveData: " << fd;
        sessions_iter_ = sessions_.find(fd);
        if (sessions_iter_ != sessions_.end())
        {
            sessions_iter_->second->Receive(data, size);
        }
        else
        {
            throw std::runtime_error("can't find session: " + std::to_string(fd));
        }
    }

    void NetworkModule::OnConnected(int fd)
    {
        LOG(INFO) << "The client connects to the server: "
                  << " [" << fd << "]";

        sessions_iter_ = sessions_.find(fd);
        if (sessions_iter_ == sessions_.end())
        {
            Session *session = new Session;
            session->Setup(fd, message_send_, message_receive_);
            sessions_.insert(std::make_pair(fd, session));

            session->Send(MessageType_Connected);
            // session->Send(Message::Global.Setup(MessageType_Connected));
        }
    }

    void NetworkModule::OnMessageSend(int fd, const char *message, size_t size)
    {
        //size_t size = message_packer_->ToBytes(message);
        // int size = sizeof(message);
        socket_->SendData(fd, message, size);
    }

    void NetworkModule::OnMessageReceive(const Session *session, IMessage *message)
    {
        for (size_t i = 0; i < message_receiver_listeners_.size(); i++)
        {
            message_receiver_listeners_[i](session, message);
        }

        delete message;
    }

    void NetworkModule::CreateServer(const char *server_ip, int server_port)
    {
        socket_->CreateListenSocket(server_ip, server_port);
        LOG(INFO) << "Server runing: " << server_ip << ":" << server_port;
    }

    void NetworkModule::CreateInnerSession(AppType_ app_type, const char *server_ip, int server_port)
    {
        LOG(INFO) << "Waiting for inner session connecting: "
                  << "[" << std::to_string(app_type) << "] " << server_ip << ":" << server_port;
        socket_->CreateConnectSocket(app_type, server_ip, server_port);
    }

    void NetworkModule::OnInnerConnected(const char name, int fd)
    {
        sessions_iter_ = sessions_.find(fd);
        if (sessions_iter_ == sessions_.end())
        {
            // LOG(INFO) << "Socket created successfully, waiting for inner session to connect to server, "
            //           << " [" << std::to_string(name) << "] "
            //           << "[" << fd << "]";
            // Session *session = new Session;
            // session->Setup(fd, message_send_, message_receive_);
            // sessions_.insert(std::make_pair(fd, session));
            // //内部的session
            // GetSystem()->GetModule<InnerSessionModule>()->AddInnerSession(name, session);
            //session->Send(Message::Setup(MessageType_Inner,));
            //S2G_RegisterInnerSession ss;
            /*     ss.set_name(name);
        ss.set_secret("7c70519a56c6c16ab2c6be0c05c6455b");*/
            //session->Send(&ss);
        }
    }

    void NetworkModule::AddReciveListener(MESSAGE_RECEIVE message_receive)
    {
        message_receiver_listeners_.push_back(message_receive);
    }

} // namespace wanderer
