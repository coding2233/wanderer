#ifndef __MESSAGE_DISPATCHER_H__
#define __MESSAGE_DISPATCHER_H__

#include "network/session.h"

#include <map>

namespace wanderer
{
class MessageDispatcher
{
private:
    /* data */
    std::map<int, google::protobuf::Message> message_;

    //void BindMessageCode()

public:
    MessageDispatcher(/* args */);
    ~MessageDispatcher();

    //分发
    void Dispatcher(const Session *session, int type, const char *data, int size);
};
} // namespace wanderer

#endif
