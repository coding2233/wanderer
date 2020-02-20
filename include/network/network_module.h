#ifndef __NETWORK_MODULE_H__
#define __NETWORK_MODULE_H__

#include "base/module.h"
#include "network/socket_epoll.h"
#include "network/session.h"
#include "network/protobuf_message_packer.h"
//#include "network/message_dispatcher.h"

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
    //消息打包
    ProtobufMessagePacker *message_packer_;
    //接收数据
    void OnReceiveData(int fd, const char *data, int size);
    //发送数据
    void OnConnected(int fd);
    //处理消息
    void OnMessageDispatcher(const Session *session, int type, const char *data, int size);
    //消息绑定回调
    // MESSAGE_CALLBACK message_callback_;
    //消息分发管理
    // MessageDispatcher *dispatcher_;

public:
    NetworkModule();
    ~NetworkModule();

    //初始化函数
    void OnInit() override;
    //循环
    void OnUpdate() override;
    //关闭
    void OnClose() override;
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