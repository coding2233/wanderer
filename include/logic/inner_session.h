#ifndef __INNER_SESSION_H__
#define __INNER_SESSION_H__

#include "logic/socket_inner_linux.h"
#include "network/session.h"
#include "network/protobuf_message_packer.h"

namespace wanderer
{
class InnerSession
{
private:
    /* data */
    SocketInnerLinux *socket_inner_;
    Session *session_;
    //接收数据
    void OnReceiveData(int fd, const char *data, int size);
    //消息打包
    ProtobufMessagePacker *message_packer_;
    //消息发送绑定
    MESSAGE_SEND message_send_;
    //消息绑定回调
    MESSAGE_RECEIVE message_receive_;
    //消息发送
    void OnMessageSend(int fd, const google::protobuf::Message &message);
    //处理消息
    void OnMessageReceive(const Session *session, int type, const char *data, int size);

public:
    InnerSession(const char *server_ip, int server_port, const char *name);
    ~InnerSession();

    void Loop();

    Session *GetSession();
};
} // namespace wanderer
#endif