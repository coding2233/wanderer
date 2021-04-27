#include "network/network_module.h"
namespace wanderer
{

    NetworkModule::NetworkModule(System *system) : Module(system)
    {
        //message_packer_ = new ProtobufMessagePacker;
#if WIN32
        throw std::runtime_error("IOCP not implemented yet!!");
        //socket_ = new SocketIOCP;
#elif unix
        socket_ = new SocketEpoll;
#endif

        message_send_ = std::bind(&NetworkModule::OnMessageSend, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
        message_receive_ = std::bind(&NetworkModule::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

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
        LOG(INFO) << "OnReceiveData: " << fd << " data:" << data << " size:" << size << " type:" << std::to_string(data[4]);
        sessions_iter_ = sessions_.find(fd);
        if (sessions_iter_ != sessions_.end())
        {
            sessions_iter_->second->Receive(data, size);
        }
        else
        {
            throw std::runtime_error("Can't find session: " + std::to_string(fd));
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
        auto ais = alltype_inner_session_.find(fd);
        if (ais != alltype_inner_session_.end())
        {
            LOG(INFO) << "Inner message session -> session: " << fd << " ---> " << ais->second << " head:" << std::to_string(message[4]) << std::endl;
            OnReceiveData(ais->second, message, size);
        }
        else
        {
            socket_->SendData(fd, message, size);
        }
    }

    void NetworkModule::OnMessageReceive(Session *session, MessageType_ message_type, const char *data, size_t size)
    {
        if (message_type == MessageType_Exchange)
        {
            auto app_type = GetSystem()->app_config_->app_type_;
            LOG(INFO) << "MessageType_Exchange " << std::to_string(app_type);
            GetSystem()->GetModule<InnerSessionModule>()->InnerAuth(session);
        }
        else if (message_type == MessageType_InnerAuth)
        {
            auto app_type = (AppType_)data[0];
            std::string secret_key(data + 1);
            LOG(INFO) << "Internal session authentication key: " << data;
            if (secret_key == GetSystem()->app_config_->secret_key_)
            {
                LOG(INFO) << "successful authentication!";
                GetSystem()->GetModule<InnerSessionModule>()->AddInnerCenterSession(app_type, session);
            }
        }

        if (GetSystem()->GetModule<InnerSessionModule>()->IsInner(session))
        {
            for (size_t i = 0; i < message_receiver_listeners_.size(); i++)
            {
                inner_message_receiver_listeners_[i](session, message_type, data, size);
            }
        }
        else
        {
            for (size_t i = 0; i < message_receiver_listeners_.size(); i++)
            {
                message_receiver_listeners_[i](session, message_type, data, size);
            }
        }
        // delete message;
    }

    void NetworkModule::CreateServer(const char *server_ip, int server_port)
    {
        socket_->CreateListenSocket(server_ip, server_port);
        LOG(INFO) << "Server runing: " << server_ip << ":" << server_port;
    }

    void NetworkModule::CreateInnerSession(AppType_ app_type, const char *server_ip, int server_port)
    {
        LOG(INFO) << "Waiting for inner session connecting, app_type: "
                  << std::to_string(app_type) << " server: " << server_ip << ":" << server_port;
        if (GetSystem()->app_config_->app_type_ == AppType_All)
        {
            int fd_c = -99 - (int)app_type;
            //模拟服务器连接
            int fd_s = -999 - (int)app_type;
            // --- 添加所有的内部通信
            alltype_inner_session_.insert(std::make_pair(fd_c, fd_s));
            alltype_inner_session_.insert(std::make_pair(fd_s, fd_c));
            //模拟连接
            OnInnerConnected(app_type, fd_c);
            OnConnected(fd_s);
        }
        else
        {
            socket_->CreateConnectSocket(app_type, server_ip, server_port);
        }
    }

    void NetworkModule::OnInnerConnected(const char name, int fd)
    {
        sessions_iter_ = sessions_.find(fd);
        if (sessions_iter_ == sessions_.end())
        {
            Session *session = new Session;
            session->Setup(fd, message_send_, message_receive_);
            sessions_.insert(std::make_pair(fd, session));
            //内部的session
            GetSystem()->GetModule<InnerSessionModule>()->AddInnerSession(name, session);
        }
    }

    void NetworkModule::AddReciveListener(MESSAGE_RECEIVE message_receive)
    {
        message_receiver_listeners_.push_back(message_receive);
    }

    void NetworkModule::AddInnerReceiveListener(MESSAGE_RECEIVE message_receive)
    {
        inner_message_receiver_listeners_.push_back(message_receive);
    }

} // namespace wanderer
