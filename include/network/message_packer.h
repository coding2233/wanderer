#ifndef __MESSAGE_PACKER_H__
#define __MESSAGE_PACKER_H__

#include "network/message.h"

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

    //转数据
    virtual int ToBytes(const T *message) = 0;

    // //转消息结构
    // Message *ToMessage(const char *buffer, int size) = 0;
};

} // namespace wanderer

#endif