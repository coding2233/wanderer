#include "network/protobuf_message_packer.h"

namespace wanderer
{

ProtobufMessagePacker::ProtobufMessagePacker(/* args */)
{
    data_ = buffer_;

    BindMessageCode(1, new wanderer::TestMessage);
    BindMessageHandler(1, new wanderer::TestMessageHandler);

    BindMessageCode(2, new wanderer::S2G_RegisterInnerSession);
    BindMessageHandler(2, new wanderer::S2G_RegisterInnerSessionHandler);
}

ProtobufMessagePacker::~ProtobufMessagePacker()
{
    //  std::map<int, google::protobuf::Message *>::iterator iter;
    for (auto iter = message_.begin(); iter != message_.end(); iter++)
    {
        delete iter->second;
    }
    message_.clear();

    for (auto iter = message_hander_.begin(); iter != message_hander_.end(); iter++)
    {
        delete iter->second;
    }
    message_hander_.clear();
}

void ProtobufMessagePacker::BindMessageCode(int type, google::protobuf::Message *message)
{
    message_.insert(std::make_pair(type, message));
    message_typeid_.insert(std::make_pair(typeid(message).name(), type));
}

void ProtobufMessagePacker::BindMessageHandler(int type, MessageHandlerBase *message_handle)
{
    message_hander_.insert(std::make_pair(type, message_handle));
}

size_t ProtobufMessagePacker::ToBytes(const google::protobuf::Message &message)
{
    memset(buffer_, 0, BUFFER_SIZE);
    auto iter = message_typeid_.find(typeid(message).name());
    if (iter != message_typeid_.end())
    {
        int type_code = iter->second;
        const size_t data_size = message.ByteSizeLong();
        size_t size = 4 + 4 + data_size;
        sprintf(data_, "%d", size);
        sprintf(data_ + 4, "%d", type_code);
        message.SerializeToArray(data_ + 8, size);
        return size;
    }

    return -1;
}

void ProtobufMessagePacker::Dispatcher(const Session *session, int type, const char *data, int size)
{
    auto iter = message_.find(type);
    if (iter != message_.end())
    {
        iter->second->ParseFromArray(data, size);

        auto message_hander_iter = message_hander_.find(type);
        if (message_hander_iter != message_hander_.end())
        {
            message_hander_iter->second->HandleMessage(session, iter->second);
        }
    }
}

char *ProtobufMessagePacker::Read() const
{
    return data_;
}

} // namespace wanderer