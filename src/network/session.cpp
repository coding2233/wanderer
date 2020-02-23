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

void Session::Setup(int fd, MESSAGE_SEND message_send, MESSAGE_RECEIVE message_receive)
{
    fd_ = fd;
    message_send_ = message_send;
    message_receive_ = message_receive;
}

void Session::Send(const google::protobuf::Message &message)
{
    message_send_(fd_, message);
}

void Session::Receive(const char *data, int size)
{
    circle_buffer_->Write(data, size);
    const char *read = circle_buffer_->Read();

    // char temp[4];
    // memcpy(temp, read, 4);
    int data_size = CharPointer2Int(read); //atoi(temp);
    if (data_size > 0 && data_size <= circle_buffer_->Length())
    {
        // memset(temp, 0, 4);
        // memcpy(temp, read + 4, 4);
        int message_type = CharPointer2Int(read + 4); // atoi(temp);
        //消息回调
        message_receive_(this, message_type, read + 8, data_size - 8);
        //清理数据
        circle_buffer_->Flush(data_size);
    }
}

// int Session::CharPointer2Int(const char *data)
// {
//     int result = 0;
//     for (size_t i = 0; i < 4; i++)
//     {
//         result |= (data[i] & 0xFF) << ((3 - i) * 8);
//     }
//     return result;
// }

} // namespace wanderer