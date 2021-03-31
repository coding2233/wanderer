//https://blog.51cto.com/9291927/2332264#h0

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "base/app_config.h"
#include "network/circle_buffer.h"

namespace wanderer
{
    struct IMessage
    {
    public:
        virtual const char *ToBytes() = 0;

        virtual IMessage *ToMessage(const char *message, int size) = 0;
    };

    enum MessageType_ : char
    {
        MessageType_Connected = 0,
        MessageType_Heartbeat = 1,
        MessageType_Normal = 99,
    };

    // enum MessageCode_ : unsigned char
    // {
    //     MessageCode_Login_C2S = 0,
    //     MessageCode_Login_S2C = 1,
    //     MessageCode_UserInfo_L2D = 2,
    //     MessageCode_UserInfo_D2L = 3,
    // };
    /*
    传输数据:
    |0000|*|
    |数据长度(int)|加密压缩过后的数据|
    
    数据格式(非加密 非压缩):
    |0(char)|*|
    |数据类型(char)|数据|

    数据类型:
    0: 连接服务器成功
    1: 心跳包
    99: 正常数据
    */
    struct Message : public IMessage
    {
    private:
        CircleBuffer buffer_;

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
        static Message Global;

        Message *Setup(MessageType_ message_type);

        // Message *Setup(MessageType_ message_type, MessageCode_ message_code, AppType_ inner_sender, AppType_ inner_receiver, const char *message);

        const char *ToBytes() override;

        IMessage *ToMessage(const char *message, int size) override;
    };

} // namespace wanderer
#endif