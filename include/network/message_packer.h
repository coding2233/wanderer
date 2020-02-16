#ifndef __MESSAGE_PACKER_H__
#define __MESSAGE_PACKER_H__

#include "network/message.h"

#include <cstdlib>

namespace wanderer
{
template <class T>
class MessagePacker
{
private:
    /* data */
public:
    MessagePacker(/* args */)
    {
    }
    ~MessagePacker()
    {
    }

    char *buffer_;

    //转数据
    virtual size_t ToBytes(const T &message) = 0;

    // //转消息结构
    // Message *ToMessage(const char *buffer, int size) = 0;
};

} // namespace wanderer

#endif