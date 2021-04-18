#include "network.h"

namespace wanderer
{
    Network::Network(/* args */)
    {
#if WIN32
        socket_ =
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
        // socket_->Send(fd,)
    }

    void Network::Update()
    {
    }

    void Network::OnReceive(int fd, const char *data, size_t size)
    {
        auto iter = receive_buffer_.find(fd);
        CircleBuffer *buffer = nullptr;
        if (iter != receive_buffer_.end())
        {
            buffer = new CircleBuffer();
            receive_buffer_.insert(std::make_pair(fd, buffer));
            iter = receive_buffer_.find(fd);
        }
        else
        {
            buffer = iter->second;
        }
        buffer->Write(data, size);
    }

}