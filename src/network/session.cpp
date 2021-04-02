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

    void Session::Send(IMessage *message)
    {
        message_send_(fd_, message->Pack(), message->Size());
    }

    //发送信息
    void Session::Send(MessageType_ message_type)
    {
        Send(Message::Global.Setup(message_type));
    }

    void Session::Receive(const char *data, int size)
    {
        circle_buffer_->Write(data, size);
        if (circle_buffer_->Length() <= 4)
        {
            return;
        }

        const char *read = circle_buffer_->Read();
        // char temp[4];
        // memcpy(temp, read, 4);
        int data_size = CharPointer2Int(circle_buffer_->Read());
        if (data_size > 0 && data_size <= circle_buffer_->Length())
        {
            auto message = Message::Global;
            // IMessage *message = new Message();
            const char *data_message = message.Unpack(read, data_size);
            LOG(INFO) << "The message received: " << std::to_string(message.message_type_);
            switch (message.message_type_)
            {
            case MessageType_Connected:
                CreateSecretKey();
                /* code */
                break;
            case MessageType_SecretKey:
                secret_key_ = std::string(data_message);
                LOG(INFO) << "secret_key_: " << secret_key_;
                break;
            default:
                message_receive_(this, (MessageType_)message.message_type_, data_message, message.Size());
                break;
            }
            //清理数据
            circle_buffer_->Flush(data_size);
        }
    }

    void Session::CreateSecretKey()
    {
        //随机生成SecretKey
        secret_key_ = "c6596580cc9c193d6b8a15becff9a31d";
        auto message = Message::Global;
        message.Setup(MessageType_SecretKey, secret_key_.c_str(), secret_key_.size());
        Send(&message);
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
