#include "network/message.h"

namespace wanderer
{
    CircleBuffer Message::buffer_;
    OpenSSLUtility Message::openssl_;

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

    const char *Message::Pack(const std::string &secret_key)
    {
        //加密 - 压缩
        if (message_type_ == MessageType_SecretKey)
        {
            //RSA加密
            const std::string data(buffer_.Read(), buffer_.Length());
            std::string encrypt_data = openssl_.EncryptRSA(data);
            buffer_.Flush();
            buffer_.Write(encrypt_data.c_str(), encrypt_data.size());
        }
        // else if (message_type_ > MessageType_Exchange)
        // {
        //     const std::string data(buffer_.Read(), buffer_.Length());
        //     std::string encrypt_data = openssl_.EncryptAES(data, secret_key);
        //     buffer_.Flush();
        //     buffer_.Write(encrypt_data.c_str(), encrypt_data.size());
        // }

        // unsigned long max_size = 1024 * 4;
        // byte *buf = new byte[max_size];
        // int z_result = compress(buf, &max_size, (const byte *)buffer_.Read(), (unsigned long)buffer_.Length());
        // std::cout << "z_result: " << z_result << "   " << buffer_.Length() << "   ---  " << max_size << std::endl;
        // delete[] buf;

        buffer_.WriteHeader(message_type_);
        return buffer_.Read();
    }

    const char *Message::Unpack(const char *message, int size, const std::string &secret_key)
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
            std::string decode_data = openssl_.DecryptRSA(data);
            buffer_.Flush();
            buffer_.Write(decode_data.c_str(), decode_data.length());
        }
        // else if (message_type_ > MessageType_Exchange)
        // {
        //     //AES解密
        //     const std::string data(buffer_.Read(), buffer_.Length());
        //     LOG(INFO) << "Message::Unpack DecryptAES: " << data << " secret_key: " << secret_key;
        //     std::string decode_data = openssl_.DecryptAES(data, secret_key);
        //     buffer_.Flush();
        //     buffer_.Write(decode_data.c_str(), decode_data.length());
        // }
        return buffer_.Read();
    }

    size_t Message::Size()
    {
        return buffer_.Length();
    }

} // namespace wanderer