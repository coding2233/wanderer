#include "network/message.h"

namespace wanderer
{
    CircleBuffer Message::buffer_;
    Message Message::Global;

    Message::Message(/* args */)
    {
    }

    Message::~Message()
    {
    }

    Message *Message::Setup(MessageType_ message_type)
    {
        buffer_.Flush();
        message_type_ = message_type;
        return this;
    }

    Message *Message::Setup(MessageType_ message_type, const char *data, size_t size)
    {
        buffer_.Flush();
        message_type_ = message_type;
        buffer_.Write(data, size);
        return this;
    }

    // Message *Message::Setup(MessageType_ message_type, MessageCode_ message_code, AppType_ inner_sender, AppType_ inner_receiver, const char *message)
    // {
    //     message_type_ = message_type;
    //     // message_code_ = message_code;
    //     // inner_sender_ = inner_sender;
    //     // inner_receiver_ = inner_receiver;
    //     // message_ = message;
    //     return this;
    // }

    const char *Message::ToBytes()
    {
        // buffer_.Write(message_type_);
        //加密 - 压缩
        buffer_.WriteHeader(message_type_);
        return buffer_.Read();
    }

    int Message::Size()
    {
        return buffer_.Length();
    }

    IMessage *Message::ToMessage(const char *message, int size)
    {
        //解压 - 解密
        message_type_ = message[0];
        // message_code_ = message[1];
        // int index = 2;
        // if (message_type_ == MessageType_Inner)
        // {
        //     inner_sender_ = message[2];
        //     inner_receiver_ = message[3];
        //     index = 4;
        // }

        return this;
    }

} // namespace wanderer