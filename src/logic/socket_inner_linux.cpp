#include "logic/socket_inner_linux.h"

namespace wanderer
{
SocketInnerLinux::SocketInnerLinux(/* args */)
{
}

SocketInnerLinux::~SocketInnerLinux()
{
}

void SocketInnerLinux::Setup(const char *server_ip, int server_port, std::function<void(int, const char *data, int size)> receiveCallback)
{
    receiveCallback_ = receiveCallback;

    socket_client_ = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in addr, server_addr;
    bzero(&addr, sizeof(addr));
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(0);
    if (bind(socket_client_, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        throw std::runtime_error("inner socket bind error!");
    }
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);
    int reseult = connect(socket_client_, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (reseult == 0)
    {
        std::cout << "connect server success!!" << std::endl;
    }
    else if (reseult < 0)
    {
        throw std::runtime_error("innner socket connect server fail !");
    }
    //设置非阻塞模式
    int flag = fcntl(socket_client_, F_GETFL, 0);
    fcntl(socket_client_, F_SETFL, flag | O_NONBLOCK);
}

void SocketInnerLinux::Loop()
{
    auto size = recv(socket_client_, buffer_, BUFFER_MAX_SIZE, 0);
    if (size > 0)
    {
        receiveCallback_(socket_client_, buffer_, size);
    }
}

int SocketInnerLinux::GetSocket()
{
    return socket_client_;
}

int SocketInnerLinux::SendData(const char *data, size_t size)
{
    return send(socket_client_, data, size, 0);
}

void SocketInnerLinux::Close()
{
    shutdown(socket_client_, SHUT_RD);
}

// void SocketInnerLinux::OnMessageReceive(const Session *session, int type, const char *data, int size)
// {
//     // message_packer_->Dispatcher(session, type, data, size);
// }

} // namespace wanderer