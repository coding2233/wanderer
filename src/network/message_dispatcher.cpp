#include "network/message_dispatcher.h"

namespace wanderer
{

MessageDispatcher::MessageDispatcher(/* args */)
{
    BindMessageCode(1, new tutorial::Person);
}

MessageDispatcher::~MessageDispatcher()
{
    std::map<int, google::protobuf::Message *>::iterator iter;
    for (iter = message_.begin(); iter != message_.end(); iter++)
    {
        delete iter->second;
    }
    message_.clear();
}

void MessageDispatcher::BindMessageCode(int type, google::protobuf::Message *message)
{
    message_.insert(std::make_pair(type, message));
}

void MessageDispatcher::Dispatcher(const Session *session, int type, const char *data, int size)
{
    auto iter = message_.find(type);
    if (iter != message_.end())
    {
        iter->second->ParseFromArray(data, size);
        /* code */
    }
}

} // namespace wanderer