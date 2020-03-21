#ifndef __PROTOBUF_MESSAGE_PACKER_H__
#define __PROTOBUF_MESSAGE_PACKER_H__

#include "network/message_packer.h"
#include "network/session.h"
#include "test.pb.h"
#include "network/message_hander_base.h"
#include "message_handler/test_message_handler.h"
#include "wanderer.pb.h"
#include "message_handler/s2g_register_inner_session_handler.h"

#include <google/protobuf/message.h>

namespace wanderer
{

class ProtobufMessagePacker : public MessagePacker<google::protobuf::Message>
{
private:
    /* data */
    std::map<int, google::protobuf::Message *> message_;
    std::map<const char *, int> message_typeid_;
    std::map<int, MessageHandlerBase *> message_hander_;

    //绑定消息
    void BindMessageCode(int type, google::protobuf::Message *message);
    //绑定消息处理
    void BindMessageHandler(int type, MessageHandlerBase *message_handle);

public:
    ProtobufMessagePacker(/* args */);
    ~ProtobufMessagePacker();

    size_t ToBytes(const google::protobuf::Message *message) override;

    void Dispatcher(const Session *session, int type, const char *data, int size);

    char *Read() const override;
};
} // namespace wanderer

#endif