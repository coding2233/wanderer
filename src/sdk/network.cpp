#include "network.h"

namespace wanderer
{
    Network::Network(/* args */)
    {
#if WIN32
        socket_ = new SocketWindows();
#elif unix
        socket_ = new SocketUnix();
#endif
        socket_->Setup(std::bind(&Network::OnReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    }

    Network::~Network()
    {
        delete socket_;
    }

    void Network::Connect(const char *server_ip, int server_port, void *receive_callback, void *connect_faile)
    {
        socket_->Connect(server_ip, server_port);
    }

    void Network::DisConnect()
    {
    }

    void Network::Send(int fd, const char *data, size_t size)
    {
        socket_->SendData(fd, data, size);
    }

    void Network::Update()
    {
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
            buffer.erase(0, data_size);
            auto msg_type = (MessageType_)message->message_type_;
            std::cout << "Message type: " << std::to_string(msg_type) << std::endl;
            if (msg_type == MessageType_Connected)
            {
                std::string secret_key = CreateSecretKey();
                std::cout << "Create secret_key:" << secret_key << std::endl;
                session_data->secret_key_ = secret_key;
                message->Setup(MessageType_SecretKey, secret_key.c_str(), secret_key.size());
                const char *data = message->Pack(secret_key);
                int size = message->Size();
                Send(fd, data, size);
            }
            else if (msg_type == MessageType_Exchange)
            {
                std::cout << "MessageType_Exchange!" << std::endl;
            }
            delete message;
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
        auto node = YAML::Load("{'id':'','pw':''}");
        node["id"] = user_name;
        node["pw"] = OpenSSLUtility::Md5(std::string(password));
        Send(login_fd_, node.data, node.size());
    }

}