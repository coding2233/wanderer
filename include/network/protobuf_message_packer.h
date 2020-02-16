#ifndef __PROTOBUF_MESSAGE_PACKER__
#define __PROTOBUF_MESSAGE_PACKER__

#include "network/message_packer.h"
#include <google/protobuf/message.h>

namespace wanderer
{
class ProtobufMessagePacker : public MessagePacker<google::protobuf::Message>
{
private:
    /* data */
public:
    ProtobufMessagePacker(/* args */);
    ~ProtobufMessagePacker();

    size_t ToBytes(const google::protobuf::Message &message) override;
};
} // namespace wanderer

#endif