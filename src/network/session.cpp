#include "network/session.h"

namespace wanderer
{

Session::Session(/* args */)
{
}

Session::~Session()
{
}

void Session::Setup(int fd, SocketBase *socket, ProtobufMessagePacker *message_packer)
{
    fd_ = fd;
    socket_ = socket;
    message_packer_ = message_packer;
}

void Session::Send(const google::protobuf::Message &message)
{
    size_t size = message_packer_->ToBytes(message);
    socket_->SendData(fd_, message_packer_->buffer_, size);
}

void Session::Receive(const char *data, int size)
{
    char temp[4];
    memcpy(temp, data, 4);
    int data_size = atoi(temp);
    memset(temp, 0, 4);
    memcpy(temp, data + 4, 2);
    int type = atoi(temp);
    // data_size |= data[1] - 48 << 16;
    // data_size |= data[2] - 48 << 8;
    // data_size |= data[3] - 48 << 0;
    // char *size_data;
    // int data_size = atoi(size_data);
    // // *data << 8;
    // int type = *(data + 4) << 8;
    // int *type = static_cast<short *>(data + 2);
    std::cout << "session receive: " << data_size << "  " << type << "  " << size << std::endl;

    // memcpy(data,)
}

} // namespace wanderer