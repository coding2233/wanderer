#include "network/network_module.h"
#include "actor/actor_inner.h"
#include "utility/jsonrpcpp.hpp"
namespace wanderer
{

    NetworkModule::NetworkModule(System *system) : Module(system)
    {
        inner_session_ = nullptr;

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
        // auto inner_connected_callback = std::bind(&NetworkModule::OnInnerConnected, this, std::placeholders::_1, std::placeholders::_2);

        socket_->Setup(connect_callback, receive_callback);
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
        auto iter = sessions_.find(fd);
        if (iter != sessions_.end())
        {
            iter->second->Receive(data, size);
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
        Session *session = SpawnSession(fd);
        session->Send(MessageType_Connected);
    }

    void NetworkModule::OnMessageSend(int fd, const char *message, size_t size)
    {
        if (fd == -99)
        {
            OnReceiveData(-999, message, size);
        }
        else if (fd == -999)
        {
            OnReceiveData(-99, message, size);
        }
        else
        {
            socket_->SendData(fd, message, size);
        }
    }

    void NetworkModule::OnMessageReceive(Session *session, MessageType_ message_type, const char *data, size_t size)
    {
        if (message_type == MessageType_Actor)
        {
            LOG(INFO) << "NetworkModule::OnMessageReceive [ActorMessage]";
            // GetSystem()->GetModule<ActorModule>()->HandleMessage(session, data, size);
            return;
        }

        if (message_type == MessageType_Exchange)
        {
            if (session == inner_session_)
            {
                auto app_type = GetSystem()->app_config_->app_type_;
                std::string secret_key = GetSystem()->app_config_->secret_key_;
                LOG(INFO) << "MessageType_Exchange " << std::to_string(app_type);
                ActorInner actor_inner;
                LOG(DEBUG) << "ActorInner actor_inner " << actor_inner.GetAddress();
                GetSystem()->GetModule<ActorModule>()->Register(&actor_inner, 0);
                session->Send((int)ActorAddress_CENTER_AUTH, actor_inner.GetAddress(), "auth", Json({(int)app_type, secret_key}));
            }
        }
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
        int fd_c = -1;
        if (app_type == AppType_All)
        {
            fd_c = -99;
            int fd_s = -999;
            inner_session_ = SpawnSession(fd_c);
            OnConnected(fd_s);
        }
        else
        {
            fd_c = socket_->CreateConnectSocket(server_ip, server_port);
            inner_session_ = SpawnSession(fd_c);
        }
    }

    Session *NetworkModule::SpawnSession(int fd)
    {
        auto iter = sessions_.find(fd);
        if (iter == sessions_.end())
        {
            Session *session = session_pool_.Pop();
            session->Setup(fd, message_send_, message_receive_);
            sessions_.insert(std::make_pair(fd, session));
            return session;
        }

        return iter->second;
    }

    // Session *NetworkModule::GetInnerSession() const
    // {
    //     return inner_session_;
    // }

} // namespace wanderer
