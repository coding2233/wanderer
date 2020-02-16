#include "network/protobuf_message_packer.h"

namespace wanderer
{

ProtobufMessagePacker::ProtobufMessagePacker(/* args */)
{
}

ProtobufMessagePacker::~ProtobufMessagePacker()
{
}

size_t ProtobufMessagePacker::ToBytes(const google::protobuf::Message &message)
{
    //清理原来的数据
    if (buffer_ != nullptr)
    {
        delete buffer_;
    }

    const size_t size = message.ByteSizeLong();
    buffer_ = new char[size];
    message.SerializeToArray(buffer_, size);

    return size;
}

} // namespace wanderer