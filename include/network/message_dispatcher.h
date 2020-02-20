#ifndef __MESSAGE_DISPATCHER_H__
#define __MESSAGE_DISPATCHER_H__

#include "network/session.h"
#include "addressbook.pb.h"

#include <map>

namespace wanderer
{

//#define MAKE_MESSAGE(class_name) []() { return class_name; }

class MessageDispatcher
{
private:
    /* data */
    std::map<int, google::protobuf::Message *> message_;
    //绑定消息
    void BindMessageCode(int type, google::protobuf::Message *message);

public:
    MessageDispatcher(/* args */);
    ~MessageDispatcher();

    //分发
    void Dispatcher(const Session *session, int type, const char *data, int size);
};
} // namespace wanderer

#endif
