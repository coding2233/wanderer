#include "network/protobuf_message_packer.h"

namespace wanderer
{

ProtobufMessagePacker::ProtobufMessagePacker(/* args */)
{
    data_ = buffer_;

    BindMessageCode(1, new wanderer::TestMessage);
}

ProtobufMessagePacker::~ProtobufMessagePacker()
{
    //  std::map<int, google::protobuf::Message *>::iterator iter;
    for (auto iter = message_.begin(); iter != message_.end(); iter++)
    {
        delete iter->second;
    }
    message_.clear();
}

void ProtobufMessagePacker::BindMessageCode(int type, google::protobuf::Message *message)
{
    message_.insert(std::make_pair(type, message));
    message_typeid_.insert(std::make_pair(typeid(message).name(), type));
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

        TestMessage *msg = dynamic_cast<TestMessage *>(iter->second);
        if (msg != nullptr)
        {
            std::cout << msg->id() << std::endl;
            std::cout << msg->name() << std::endl;
            std::cout << msg->content() << std::endl;
        }
        /* code */
    }
}

char *ProtobufMessagePacker::Read() const
{
    return data_;
}

} // namespace wanderer