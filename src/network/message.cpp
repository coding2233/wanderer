#include "network/message.h"

namespace wanderer
{
    CircleBuffer Message::buffer_;
    Message Message::Global;

    Message::Message(/* args */)
    {
        openssl_ = new OpenSSLUtility();
    }

    Message::~Message()
    {
        delete openssl_;
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
        if (message_type_ == MessageType_SecretKey)
        {
            //RSA加密
            const std::string data(buffer_.Read(), buffer_.Length());
            std::string encrypt_data = openssl_->EncryptRSA(data);
            buffer_.Flush();
            buffer_.Write(encrypt_data.c_str(), encrypt_data.size());
        }
        buffer_.WriteHeader(message_type_);
        return buffer_.Read();
    }

    const char *Message::Unpack(const char *message, int size)
    {
        //解压 - 解密
        message_type_ = message[4];
        buffer_.Flush();
        buffer_.Write(message + 5, size - 5);

        //加密 - 压缩
        if (message_type_ == MessageType_SecretKey)
        {
            //RSA解密
            const std::string data(buffer_.Read(), buffer_.Length());
            std::string decode_data = openssl_->DecodeRSA(data);
            LOG(INFO) << "---" << decode_data;
            buffer_.Flush();
            buffer_.Write(decode_data.c_str(), decode_data.length());
        }
        return buffer_.Read();
    }

    size_t Message::Size()
    {
        return buffer_.Length();
    }

} // namespace wanderer