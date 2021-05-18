//https://blog.51cto.com/9291927/2332264#h0

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "base/app_config.h"
#include "base/easylogging++.h"
#include "network/circle_buffer.h"
#include "utility/jsonrpcpp.hpp"
#include "utility/openssl_utility.h"

// #include "zlib.h"
namespace wanderer
{
    struct IMessage
    {
    public:
        virtual const char *Pack(const std::string &secret_key) = 0;
        virtual const char *Unpack(const char *message, int size, const std::string &secret_key) = 0;
        virtual size_t Size() = 0;
    };

    enum MessageType_ : char
    {
        //服务器接收到客户端的连接 S->C
        MessageType_Connected = 0,
        //客户端的密钥 C->S
        MessageType_SecretKey = 1,
        //可通信交流 S->C
        MessageType_Exchange = 2,

        //actor消息 - 普通消息
        MessageType_Actor = 99,
    };

    /*
    传输数据:
    |0000|*|
    |数据长度(int)|加密压缩过后的数据|
    
    数据格式(非加密 非压缩):
    |0(char)|*|
    |数据类型(char)|数据|

    数据类型:
    0: 连接服务器成功
    1: AES加密密钥
    2: 心跳包
    99: 正常数据

    加密:
    服务器接收客户端连接成功->客户端生成AES密钥->客户端通过RSA加密传输给服务端->服务器接收AES密钥并作为网络数据的传输加密.
    */
    struct Message : public IMessage
    {
    protected:
        static CircleBuffer buffer_;

        static OpenSSLUtility openssl_;

    public:
        Message(/* args */);
        ~Message();

        //MessageType_
        char message_type_;
        // //MessageCode_
        // unsigned char message_code_;
        // //AppType_
        // char inner_sender_;
        // //AppType_
        // char inner_receiver_;
        // Message content
        // const char *message_;

        //The global object of the message.
        // static Message Global;

        Message *Setup(MessageType_ message_type);

        Message *Setup(MessageType_ message_type, const char *data, size_t size);

        Message *Setup(MessageType_ message_type, int to_address, int from_address, jsonrpcpp::entity_ptr message_entilty);

        // Message *Setup(MessageType_ message_type, MessageCode_ message_code, AppType_ inner_sender, AppType_ inner_receiver, const char *message);

        const char *Pack(const std::string &secret_key) override;
        const char *Unpack(const char *message, int size, const std::string &secret_key) override;

        size_t Size() override;
    };

} // namespace wanderer
#endif