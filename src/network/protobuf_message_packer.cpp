#include "network/protobuf_message_packer.h"

namespace wanderer
{

ProtobufMessagePacker::ProtobufMessagePacker(/* args */)
{
}

ProtobufMessagePacker::~ProtobufMessagePacker()
{
}

int ProtobufMessagePacker::ToBytes(const google::protobuf::Message *message)
{
    const size_t size = message->ByteSizeLong();
    char data[size];
    message->SerializeToArray(&data, size);

    return 0;
}

} // namespace wanderer