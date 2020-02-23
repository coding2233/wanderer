#ifndef __PROTOBUF_MESSAGE_PACKER_H__
#define __PROTOBUF_MESSAGE_PACKER_H__

#include "network/message_packer.h"
//#include "network/session.h"
#include "test.pb.h"

#include <google/protobuf/message.h>

namespace wanderer
{
class Session;

class ProtobufMessagePacker : public MessagePacker<google::protobuf::Message>
{
private:
    /* data */
    std::map<int, google::protobuf::Message *> message_;
    std::map<const char *, int> message_typeid_;

    //绑定消息
    void BindMessageCode(int type, google::protobuf::Message *message);

public:
    ProtobufMessagePacker(/* args */);
    ~ProtobufMessagePacker();

    size_t ToBytes(const google::protobuf::Message &message) override;

    void Dispatcher(const Session *session, int type, const char *data, int size);

    char *Read() const override;
};
} // namespace wanderer

#endif