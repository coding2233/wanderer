#include "network/message.h"

namespace wanderer
{
    Message::Message(/* args */)
    {
    }

    Message::~Message()
    {
    }

    Message* Message::Setup(MessageType_ message_type, MessageCode_ message_code, const char* message)
    {
        message_type_ = message_type;
        message_code_ = message_code;
        message_ = message;
        return this;
    }

    Message* Message::Setup(MessageType_ message_type, MessageCode_ message_code, AppType_ inner_sender, AppType_ inner_receiver, const char* message)
    {
        message_type_ = message_type;
        message_code_ = message_code;
        inner_sender_ = inner_sender;
        inner_receiver_ = inner_receiver;
        message_ = message;
        return this;
    }

    const char *Message::ToBytes()
    {
        //inner
        if (message_type_==MessageType_Inner)
        {

        }
        //outer
        else if(message_type_== MessageType_Outer)
        {

        }
        return "";
    }

    IMessage* Message::ToMessage(const char* message, int size)
    {
        message_type_ = message[0];
        message_code_ = message[1];
        int index = 2;
        if (message_type_ == MessageType_Inner)
        {
            inner_sender_ = message[2];
            inner_receiver_ = message[3];
            index = 4;
        }

        return this;
    }

} // namespace wanderer