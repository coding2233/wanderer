#include "network/message.h"

namespace wanderer
{
    Message::Message(/* args */)
    {
    }

    Message::~Message()
    {
    }

    Message* Message::Setup(MessageType_ message_type, const char* message)
    {
        message_type_ = message_type;
        message_ = message;
        return this;
    }

    Message* Message::Setup(MessageType_ message_type, AppType_ inner_sender, AppType_ inner_receiver, const char* message)
    {
        message_type_ = message_type;
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
        return this;
    }

} // namespace wanderer