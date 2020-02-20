#include "network/session.h"

namespace wanderer
{

Session::Session(/* args */)
{
    circle_buffer_ = new CircleBuffer;
}

Session::~Session()
{
    delete circle_buffer_;
}

void Session::Setup(int fd, SocketBase *socket, ProtobufMessagePacker *message_packer)
{
    fd_ = fd;
    socket_ = socket;
    message_packer_ = message_packer;
    //  message_callback_ = message_callback;
}

void Session::Send(const google::protobuf::Message &message)
{
    size_t size = message_packer_->ToBytes(message);
    socket_->SendData(fd_, message_packer_->Read(), size);
}

void Session::Receive(const char *data, int size)
{
    circle_buffer_->Write(data, size);
    const char *read = circle_buffer_->Read();

    char temp[4];
    memcpy(temp, read, 4);
    int data_size = atoi(temp);
    if (data_size <= circle_buffer_->Length())
    {
        memset(temp, 0, 4);
        memcpy(temp, read + 4, 4);
        int message_type = atoi(temp);
        //消息回调
        message_packer_->Dispatcher(this, message_type, read + 8, data_size - 8);
        //  message_callback_(this, message_type, read, data_size - 6);
        //清理数据
        circle_buffer_->Flush(data_size);
    }

    //   std::cout << "session receive: " << data_size << "  " << type << "  " << size << std::endl;
}

} // namespace wanderer