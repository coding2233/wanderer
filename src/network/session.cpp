#include "network/session.h"
#include "utility/jsonrpcpp.hpp"
#include "utility/pool.h"
#include <memory>
#include <string>

namespace wanderer
{

    Session::Session(/* args */)
    {
        circle_buffer_ = nullptr;
        // circle_buffer_ = new CircleBuffer;
    }

    Session::~Session()
    {
        // delete circle_buffer_;
    }

    void Session::Setup(int fd, MESSAGE_SEND message_send, MESSAGE_RECEIVE message_receive)
    {
        // inner_auth_ = false;
        fd_ = fd;
        message_send_ = message_send;
        message_receive_ = message_receive;

        request_index_ = 0;
    }

    void Session::Send(IMessage *message)
    {
        const char *data = message->Pack(secret_key_);
        int size = message->Size();
        LOG(INFO) << "Session send: " << std::to_string(data[4]) << "  " << size;
        message_send_(fd_, data, size);
    }

    //发送信息
    void Session::Send(MessageType_ message_type)
    {
        Message *message = new Message();
        message->Setup(message_type);
        Send(message);
        delete message;
    }

    //发送信息
    void Session::Send(MessageType_ message_type, const char *data, size_t size)
    {
        Message *message = new Message();
        message->Setup(message_type, data, size);
        Send(message);
        delete message;
    }

    void Session::Send(int to_address, int from_address, const std::string &method, const jsonrpcpp::Parameter &params)
    {
        auto request = std::make_shared<jsonrpcpp::Request>(request_index_++, method, params);
        Send(to_address, from_address, request);
    }

    void Session::Send(int to_address, int from_address, jsonrpcpp::entity_ptr message_entilty)
    {
        LOG(DEBUG) << to_address << "  " << from_address << "  " << message_entilty->to_json().dump();
        Message message;
        message.Setup(MessageType_Actor, to_address, from_address, message_entilty);
        Send(&message);
        // delete message;
    }

    //内部认证
    // void Session::InnerAuth(AppType_ app_type)
    // {
    //     if (inner_auth_)
    //     {
    //         return;
    //     }

    //     std::string auth_str_data = std::to_string((char)app_type) + System::app_config_->secret_key_;
    //     const char *auth_data = auth_str_data.c_str();
    //     LOG(INFO) << "Internal authentication request: " << std::to_string(app_type) << " " << System::app_config_->secret_key_;
    //     Message *auth_message = new Message();
    //     auth_message->Setup(MessageType_InnerAuth, auth_data, auth_str_data.size());
    //     Send(auth_message);
    //     delete auth_message;
    //     inner_auth_ = true;
    // }

    void Session::Receive(const char *data, int size)
    {
        CheckCircleBuffer(true);

        circle_buffer_->Write(data, size);
        if (circle_buffer_->Length() < 5)
        {
            return;
        }

        const char *read = circle_buffer_->Read();
        // char temp[4];
        // memcpy(temp, read, 4);
        int data_size = CharPointer2Int(circle_buffer_->Read());

        LOG(INFO) << "[" << fd_ << "] Session::Receive size: " << data_size << " type:" << std::to_string(data[4]);

        if (data_size > 0 && data_size <= circle_buffer_->Length())
        {
            Message *message = new Message();
            const char *data_message = message->Unpack(read, data_size, secret_key_);
            LOG(INFO) << "The message received: " << std::to_string(message->message_type_);
            //清理数据
            circle_buffer_->Flush(data_size);
            auto msg_type = (MessageType_)message->message_type_;
            if (msg_type == MessageType_Connected)
            {
                CreateSecretKey();
            }
            else if (msg_type == MessageType_SecretKey)
            {
                secret_key_ = std::string(data_message, message->Size());
                LOG(INFO) << "Server-session set secret_key_: [" << fd_ << "] " << secret_key_;
            }
            else
            {
            }
            //回调
            message_receive_(this, (MessageType_)message->message_type_, data_message, message->Size());

            delete message;
        }

        CheckCircleBuffer(false);
    }

    void Session::CreateSecretKey()
    {
        //随机生成SecretKey
        int key_size = 16;
        char *secret_key = new char[key_size];
        OpenSSLUtility::RandSecretKey(secret_key, key_size);
        secret_key_ = std::string(secret_key, key_size); //"F5/kqUxo/4mkMCMD:14,079";
        LOG(INFO) << "Client-session create secret_key_: [" << fd_ << "] " << secret_key_;
        Message *message = new Message();
        message->Setup(MessageType_SecretKey, secret_key_.c_str(), secret_key_.size());
        Send(message);
        delete message;
        delete[] secret_key;
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

    void Session::CheckCircleBuffer(bool get)
    {
        static Pool<CircleBuffer> circle_buffer_pool;
        if (get)
        {
            if (circle_buffer_ == nullptr)
            {
                circle_buffer_ = circle_buffer_pool.Pop();
            }
        }
        else
        {
            if (circle_buffer_ != nullptr && circle_buffer_->Length() == 0)
            {
                circle_buffer_pool.Pop();
                circle_buffer_ = nullptr;
            }
        }
    }

} // namespace wanderer
