#include "network.h"
#include <ostream>

namespace wanderer
{
    Network::Network(/* args */)
    {
#if WIN32
        socket_ = new SocketWindows;
#elif unix
        socket_ = new SocketUnix;
#endif
        socket_->Setup(std::bind(&Network::OnReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    Network::~Network()
    {
        delete socket_;
    }

    int Network::Connect(const char *server_ip, int server_port)
    {
        std::cout<<"Network connect !ip:"<<server_ip<<" port:"<<server_port<<" ## "<<std::endl;
        // SocketUnix su;
        socket_->Connect(server_ip, server_port);
        // int fd= socket_->Connect(server_ip, server_port);
        // if (login_fd_ == 0)
        // {
        //     login_connected_ = false;
        //     login_fd_ = fd;
        // }
        // else
        // {
        //     gateway_fd_ = fd;
        // }
        // return fd;
        return 0;
    }

    void Network::DisConnect()
    {
        // if (login_fd_ > 0)
        // {
        //     socket_->Disconnect(login_fd_);
        //     login_fd_ = 0;
        // }
        // if (gateway_fd_ > 0)
        // {
        //     socket_->Disconnect(gateway_fd_);
        //     gateway_fd_ = 0;
        // }
    }

    void Network::Send(int fd, IMessage *message)
    {
        // auto iter = sessions_.find(fd);
        // if (iter != sessions_.end())
        // {
        //     const char *data = message->Pack(iter->second->secret_key_);
        //     int size = message->Size();
        //     socket_->SendData(fd, data, size);
        // }
    }

    void Network::Update()
    {
        // socket_->Update();
    }

    void Network::OnReceive(int fd, const char *data, size_t size)
    {
        std::cout << "socket receive: " << fd << " data:" << data << " size:" << size << std::endl;

        auto iter = sessions_.find(fd);
        SessionData *session_data = nullptr;
        if (iter == sessions_.end())
        {
            session_data = new SessionData();
            sessions_.insert(std::make_pair(fd, session_data));
            iter = sessions_.find(fd);
        }
        else
        {
            session_data = iter->second;
        }
        std::string &buffer = session_data->buffer_;
        buffer.append(data, size);

        if (buffer.size() < 5)
        {
            return;
        }

        const char *read_buffer = (const char *)buffer.c_str();
        int data_size = CharPointer2Int(read_buffer);
        std::cout << "read_buffer size:" << data_size << std::endl;
        if (data_size > 0 && data_size <= buffer.size())
        {
            Message *message = new Message();
            const char *data_message = message->Unpack(read_buffer, data_size, session_data->secret_key_);
            int data_message_size = message->Size();
            buffer.erase(0, data_size);
            auto msg_type = (MessageType_)message->message_type_;
            std::cout << "Message type: " << std::to_string(msg_type) << std::endl;
            if (msg_type == MessageType_Connected)
            {
                std::string secret_key = CreateSecretKey();
                std::cout << "Create secret_key:" << secret_key << std::endl;
                session_data->secret_key_ = secret_key;
                message->Setup(MessageType_SecretKey, secret_key.c_str(), secret_key.size());
                // const char *data = message->Pack(secret_key);
                // int size = message->Size();
                Send(fd, message);
            }
            else if (msg_type == MessageType_Exchange)
            {
                std::cout << "MessageType_Exchange!" << std::endl;
                if (fd == login_fd_)
                {
                    login_connected_ = true;
                }

                // if (fd == gateway_fd_)
                // {
                // }
            }
            else
            {
                YAML::Node node_message = YAML::Load(std::string(data_message, data_message_size));
                OnYAMLReceive(fd, node_message);
            }
            delete message;
        }
    }

    void Network::OnYAMLReceive(int fd, YAML::Node node_message)
    {
        if (fd == login_fd_)
        {
            auto gateway_ip = node_message["gateway_ip"].as<std::string>();
            auto gateway_port = node_message["gateway_port"].as<int>();
            gateway_key_ = node_message["gateway_key"].as<std::string>();
            Connect(gateway_ip.c_str(), gateway_port);
        }
        else if (fd == gateway_fd_)
        {
        }
    }

    std::string Network::CreateSecretKey()
    {
        int key_size = 16;
        char *secret_data = new char[key_size];
        OpenSSLUtility::RandSecretKey(secret_data, key_size);
        std::string secret_key = std::string(secret_data, key_size);
        delete[] secret_data;
        return secret_key;
    }

    void Network::Login(const char *user_name, const char *password)
    {
        if (!login_connected_)
        {
            return;
        }

        auto node = YAML::Load("{'id':'','pw':''}");
        node["id"] = user_name;
        node["pw"] = OpenSSLUtility::Md5(std::string(password));

        Message message;
        std::string data = node.as<std::string>();
        message.Setup(MessageType_2L, (const char *)data.c_str(), data.size());
        Send(login_fd_, &message);
    }

}