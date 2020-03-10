#ifndef __NETWORK_MODULE_H__
#define __NETWORK_MODULE_H__

#include "base/module.h"
#include "network/socket_epoll.h"
#include "network/session.h"
#include "network/protobuf_message_packer.h"

#include <functional>
#include <map>

namespace wanderer
{

#define SERVER_PORT 2233

class NetworkModule : public Module
{

private:
    //socket epoll
    SocketBase *socket_;
    //session map
    std::map<int, Session *> sessions_;
    std::map<int, Session *>::iterator sessions_iter_;
    //inner session map
    std::map<std::string, Session *> inner_session_;
    std::map<std::string, Session *>::iterator inner_session_iter_;
    //消息打包
    ProtobufMessagePacker *message_packer_;
    //消息发送绑定
    MESSAGE_SEND message_send_;
    //消息绑定回调
    MESSAGE_RECEIVE message_receive_;
    //接收数据
    void OnReceiveData(int fd, const char *data, int size);
    //发送数据
    void OnConnected(int fd);
    //消息发送
    void OnMessageSend(int fd, const google::protobuf::Message &message);
    //处理消息
    void OnMessageReceive(const Session *session, int type, const char *data, int size);

public:
    NetworkModule();
    ~NetworkModule();

    //初始化函数
    void OnInit() override;
    //循环
    void OnUpdate() override;
    //关闭
    void OnClose() override;
    //创建服务器
    void CreateServer(const char *server_ip, int server_port);
    //创建内部的交流通信
    void CreateInnerSession(const char *name, const char *server_ip, int server_port);
};

// #ifdef __cplusplus
// extern "C"
// {
// #endif
//     void *CreateNetworkModule();
// #ifdef __cplusplus
// }
// #endif
} // namespace wanderer
#endif