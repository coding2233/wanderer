//https://blog.51cto.com/9291927/2332264#h0

#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "base/app_config.h"

namespace wanderer
{
    struct IMessage
    {
    public:
        virtual const char *ToBytes() = 0;

        virtual IMessage* ToMessage(const char* message,int size) = 0;
    };

    enum MessageType_ :char
    {
        MessageType_Inner = 1 << 0,
        MessageType_Outer = 1 << 1
    };

    enum MessageCode_:unsigned char
    {
        MessageCode_Login_C2S=0,
        MessageCode_Login_S2C=1,
        MessageCode_UserInfo_L2D=2,
        MessageCode_UserInfo_D2L = 3,
    };

    struct Message : public IMessage
    {
    private:
       
    public:
        Message(/* args */);
        ~Message();

        //MessageType_
        char message_type_;
        //MessageCode_
        unsigned char message_code_;
        //AppType_ 
        char inner_sender_;
        //AppType_
        char inner_receiver_;
        // Message content
        const char* message_;

        //The global object of the message.
        static Message Global;

        Message* Setup(MessageType_ message_type, MessageCode_ message_code, const char* message);

        Message* Setup(MessageType_ message_type, MessageCode_ message_code, AppType_ inner_sender, AppType_ inner_receiver, const char* message);

        const char *ToBytes() override;

        IMessage* ToMessage(const char* message, int size) override;
    };

} // namespace wanderer
#endif