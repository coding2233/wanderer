#ifndef __MESSAGE_HANDER_H__
#define __MESSAGE_HANDER_H__

#include "network/message_hander_base.h"

namespace wanderer
{

template <class T>
class MessageHandler : public MessageHandlerBase
{
private:
    /* data */
public:
    MessageHandler(/* args */)
    {
    }
    ~MessageHandler()
    {
    }
    //处理消息
    void HandleMessage(const Session *session,char *message) override
    {
        T *t = dynamic_cast<T *>(message);
        Handle(session, t);
    }

protected:
    //处理消息
    virtual void Handle(const Session *session, T *message) = 0;
};
} // namespace wanderer
#endif