#ifndef __MESSAGE_PACKER_H__
#define __MESSAGE_PACKER_H__

#include "network/message.h"

namespace wanderer
{
class MessagePacker
{
private:
    /* data */
public:
    MessagePacker(/* args */);
    ~MessagePacker();

    // //转数据
    // int ToBytes(Message *message) = 0;

    // //转消息结构
    // Message *ToMessage(const char *buffer, int size) = 0;
};

} // namespace wanderer

#endif