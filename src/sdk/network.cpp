#include "network.h"
#include "network/message.h"
#include "utility/jsonrpcpp.hpp"
#include <iostream>
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

        std::cout << "socket_ address:" << socket_ << std::endl;
    }

    Network::~Network()
    {
        std::cout << "Network::~Network() " << std::endl;
        delete socket_;
    }

    int Network::Connect(const char *server_ip, int server_port, CONNECT_CALLBACK connect_callback)
    {
        if (login_connected_)
        {
            connect_callback(false, "The login server has been connected.");
            return -1;
        }
        connect_callback_ = connect_callback;
        std::cout << "Network connect !ip:" << server_ip << " port:" << server_port << std::endl;

        try
        {
            int fd = socket_->Connect(server_ip, server_port);
            login_fd_ = fd;
            login_connected_ = true;
            return fd;
        }
        catch(const std::exception& e)
        {
            // std::cerr << e.what() << '\n';
            connect_callback(false,e.what());
            std::cout<< e.what() << std::endl;
        }
        return -1;
    }

    int Network::ConnectGateway(const char *server_ip, int server_port)
    {
        std::cout << "Network ConnectGateway !ip:" << server_ip << " port:" << server_port << std::endl;
        int fd = socket_->Connect(server_ip, server_port);
        gateway_fd_ = fd;
        gateway_connected_ = true;
        return fd;
    }

    void Network::DisConnect()
    {
        if (login_fd_ > 0)
        {
            socket_->Disconnect(login_fd_);
            login_fd_ = 0;
        }
        if (gateway_fd_ > 0)
        {
            socket_->Disconnect(gateway_fd_);
            gateway_fd_ = 0;
        }
    }

    void Network::Send(int fd, IMessage *message)
    {
        auto iter = sessions_.find(fd);
        if (iter != sessions_.end())
        {
            const char *data = message->Pack(iter->second->secret_key_);
            int size = message->Size();
            socket_->SendData(fd, data, size);
        }
    }

    void Network::Update()
    {
        socket_->Update();
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
                int address = CharPointer2Int(data_message);
                if (fd == login_fd_)
                {
                    login_address_ = address;
                    connect_callback_(true, "");
                }
                else if (fd == gateway_fd_)
                {
                    gateway_address_ = address;
                }
            }
            else
            {
                jsonrpcpp::entity_ptr entity = jsonrpc_parser_.parse(std::string(data_message + 8, data_message_size - 8));
                OnJsonRpcReceive(fd, entity);
            }
            delete message;
        }
    }

    void Network::OnJsonRpcReceive(int fd, jsonrpcpp::entity_ptr entity)
    {
        if (entity)
        {
            if (entity->is_response())
            {
                std::cout << "entity->is_response(): " << entity->to_json().dump() << std::endl;
            }
        }
        // if (fd == login_fd_)
        // {
        //     auto gateway_ip = node_message["gateway_ip"].as<std::string>();
        //     auto gateway_port = node_message["gateway_port"].as<int>();
        //     gateway_key_ = node_message["gateway_key"].as<std::string>();
        //     Connect(gateway_ip.c_str(), gateway_port);
        // }
        // else if (fd == gateway_fd_)
        // {
        // }
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

    void Network::Login(const char *user_name, const char *password, LOGIN_CALLBACK login_callback)
    {
        if (!login_connected_)
        {
            return;
        }

        std::string passwd = OpenSSLUtility::Md5(std::string(password));
        login_callback_ = login_callback;
        Json login_json = {{"username", user_name},
                           {"password", passwd.c_str()}};
        jsonrpcpp::request_ptr login_request = std::make_shared<jsonrpcpp::Request>(request_index_++, "login", login_json);
        // auto data = login_request.to_json().dump();
        // std::string message_data(data.c_str(), data.size());
        Message message;
        message.Setup(MessageType_Actor, ActorAddress_LOGIN, login_address_, login_request);
        Send(login_fd_, &message);
    }

}