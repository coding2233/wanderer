#ifndef __MESSAGE_HANDER_BASE_H__
#define __MESSAGE_HANDER_BASE_H__

//#include "google/protobuf/message.h"
#include "network/session.h"

namespace wanderer
{
class MessageHandlerBase
{
private:
    /* data */
public:
    MessageHandlerBase(/* args */);
    ~MessageHandlerBase();
    //处理消息
    virtual void HandleMessage(const Session *session, char *message) = 0;
};

} // namespace wanderer
#endif