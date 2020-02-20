#ifndef __SESSION_H__
#define __SESSION_H__

#include "network/socket_base.h"
#include "network/protobuf_message_packer.h"
#include "network/circle_buffer.h"

namespace wanderer
{

//#define MESSAGE_CALLBACK std::function<void(const Session *, int, const char *, int)>

class Session
{
private:
    /* data */
    int fd_;
    SocketBase *socket_;
    ProtobufMessagePacker *message_packer_;
    //  MESSAGE_CALLBACK message_callback_;

    //circle buffer
    CircleBuffer *circle_buffer_;

public:
    Session(/* args */);
    ~Session();

    void Setup(int fd, SocketBase *socket, ProtobufMessagePacker *message_packer);

    //发送信息
    void Send(const google::protobuf::Message &message);
    //接收的数据
    void Receive(const char *data, int size);
};

} // namespace wanderer

#endif