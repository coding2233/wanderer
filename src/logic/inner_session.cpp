#include "logic/inner_session.h"

namespace wanderer
{

InnerSession::InnerSession(const char *server_ip, int server_port, const char *name)
{
    message_packer_ = new ProtobufMessagePacker;

    auto receiveCallback = std::bind(&InnerSession::OnReceiveData, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    socket_inner_ = new SocketInnerLinux;
    socket_inner_->Setup(server_ip, server_port, receiveCallback);

    message_send_ = std::bind(&InnerSession::OnMessageSend, this, std::placeholders::_1, std::placeholders::_2);
    message_receive_ = std::bind(&InnerSession::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);

    session_ = new Session;
    session_->Setup(socket_inner_->GetSocket(), message_send_, message_receive_);
}

InnerSession::~InnerSession()
{
    delete message_packer_;
    delete socket_inner_;
}

void InnerSession::OnReceiveData(int fd, const char *data, int size)
{
    session_->Receive(data, size);
}

void InnerSession::OnMessageSend(int fd, const google::protobuf::Message &message)
{
    size_t size = message_packer_->ToBytes(message);
    socket_inner_->SendData(message_packer_->Read(), size);
}

void InnerSession::OnMessageReceive(const Session *session, int type, const char *data, int size)
{
    message_packer_->Dispatcher(session, type, data, size);
}

void InnerSession::Loop()
{
    if (socket_inner_ != nullptr)
    {
        socket_inner_->Loop();
    }
}

Session *InnerSession::GetSession()
{
    return session_;
}

} // namespace wanderer