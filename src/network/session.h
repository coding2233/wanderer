#ifndef __SESSION_H__
#define __SESSION_H__

#include <functional>

#include "network/circle_buffer.h"
#include "utility/utility.h"
#include "network/message.h"

namespace wanderer
{

#define MESSAGE_SEND std::function<void(int, const char *)>
#define MESSAGE_RECEIVE std::function<void(const Session *, IMessage*)>

    class Session
    {
    private:
        /* data */
        int fd_;
        //   SocketBase *socket_;
        //   ProtobufMessagePacker *message_packer_;
        //  MESSAGE_CALLBACK message_callback_;

        //circle buffer
        CircleBuffer *circle_buffer_;

        //  int CharPointer2Int(const char *data);

        MESSAGE_SEND message_send_;
        MESSAGE_RECEIVE message_receive_;

    public:
        Session(/* args */);
        ~Session();

        void Setup(int fd, MESSAGE_SEND message_send, MESSAGE_RECEIVE message_receive);
        //发送信息
        void Send(IMessage *message);
        //接收的数据
        void Receive(const char *data, int size);
    };

} // namespace wanderer

#endif