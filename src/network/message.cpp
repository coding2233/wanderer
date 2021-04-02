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

    const char *Message::Pack()
    {
        //加密 - 压缩
        //openssl
        switch (message_type_)
        {
        case MessageType_Connected:
            //无加密
            break;
        case MessageType_SecretKey:
            //RSA加密
            break;
        default:
            //AES加密
            break;
        }
        buffer_.WriteHeader(message_type_);
        return buffer_.Read();
    }

    const char *Message::Unpack(const char *message, int size)
    {
        //解压 - 解密
        message_type_ = message[4];
        switch (message_type_)
        {
        case MessageType_Connected:
            //无加密
            break;
        case MessageType_SecretKey:
            //RSA解密
            break;
        default:
            //AES解密
            break;
        }
        buffer_.Flush();
        buffer_.Write(message + 5, size - 5);
        return buffer_.Read();
    }

    size_t Message::Size()
    {
        return buffer_.Length();
    }

} // namespace wanderer