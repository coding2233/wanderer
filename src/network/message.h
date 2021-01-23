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

    struct Message : public IMessage
    {
    private:
        //MessageType_
        char message_type_;
        //AppType_ 
        char inner_sender_;
        //AppType_
        char inner_receiver_;
        // Message content
        const char* message_;
    public:
        Message(/* args */);
        ~Message();

        //The global object of the message.
        static Message Global;

        Message* Setup(MessageType_ message_type, const char* message);

        Message* Setup(MessageType_ message_type, AppType_ inner_sender, AppType_ inner_receiver, const char* message);

        const char *ToBytes() override;

        IMessage* ToMessage(const char* message, int size) override;
    };

} // namespace wanderer
#endif