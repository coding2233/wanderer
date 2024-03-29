#ifndef __NETWORK_MODULE_H__
#define __NETWORK_MODULE_H__

#include <functional>
#include <map>
#include <queue>

#include "actor/actor_auth.h"
#include "actor/actor_module.h"
#include "base/app_config.h"
#include "base/module.h"
#include "network/circle_buffer.h"
#include "network/socket_base.h"
#if unix
#include "network/socket_epoll.h"
#elif WIN32
#include "network/socket_iocp.h"
#endif
#include "network/session.h"
//#include "network/protobuf_message_packer.h"
#include "utility/jsonrpcpp.hpp"
#include "utility/pool.h"

namespace wanderer
{

    //#define SERVER_PORT 2233

    class NetworkModule : public Module
    {
    private:
        //socket epoll
        SocketBase *socket_;
        //Session pool
        Pool<Session> session_pool_;
        //session map
        std::map<int, Session *> sessions_;

        //非center服务器都会由这个session
        Session *inner_session_;
        //内部会话是否通过验证
        bool inner_session_auth_;

        //消息发送绑定
        MESSAGE_SEND message_send_;
        //消息绑定回调
        MESSAGE_RECEIVE message_receive_;
        //接收数据
        void OnReceiveData(int fd, const char *data, int size);
        //发送数据
        void OnConnected(int fd);
        //消息发送
        void OnMessageSend(int fd, const char *message, size_t size);
        //处理消息
        void OnMessageReceive(Session *session, MessageType_, const char *, size_t);

    public:
        NetworkModule(System *system);
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
        void CreateInnerSession(AppType_ app_type, const char *server_ip, int server_port);

        // void AddReciveListener(MESSAGE_RECEIVE message_receive);
        // void AddInnerReceiveListener(MessageType_ message_type,MESSAGE_INNER_RECEIVE message_receive);
        //void RemoveReciveListener(MESSAGE_RECEIVE& message_receive);

        Session *SpawnSession(int fd);

        void InnerSessionAuth(bool success);

        Session *GetInnerSession();
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
