#ifndef __SESSION_H__
#define __SESSION_H__

#include <functional>

#include "base/system.h"
#include "network/circle_buffer.h"
#include "network/message.h"
#include "utility/openssl_utility.h"
#include "utility/utility.h"
#include "utility/jsonrpcpp.hpp"

namespace wanderer
{

#define MESSAGE_SEND std::function<void(int, const char *, size_t)>
#define MESSAGE_RECEIVE std::function<void(Session *, MessageType_, const char *, size_t)>
#define MESSAGE_INNER_RECEIVE std::function<void(Session*,MessageType_,jsonrpcpp::entity_ptr)>

    class Session
    {
    private:
        /* data */
        int fd_;
        //AES密钥
        std::string secret_key_;

        //   SocketBase *socket_;
        //   ProtobufMessagePacker *message_packer_;
        //  MESSAGE_CALLBACK message_callback_;

        //circle buffer
        CircleBuffer *circle_buffer_;

        //  int CharPointer2Int(const char *data);

        MESSAGE_SEND message_send_;
        MESSAGE_RECEIVE message_receive_;

        //创建密钥
        void CreateSecretKey();

        bool inner_auth_ = false;

    public:
        Session(/* args */);
        ~Session();

        void Setup(int fd, MESSAGE_SEND message_send, MESSAGE_RECEIVE message_receive);
        //发送信息
        void Send(IMessage *message);
        //发送信息
        void Send(MessageType_ message_type);
        //内部认证
        void InnerAuth(AppType_ app_type);
        //接收的数据
        void Receive(const char *data, int size);
    };

} // namespace wanderer

#endif