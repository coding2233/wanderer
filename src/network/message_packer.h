#ifndef __MESSAGE_PACKER_H__
#define __MESSAGE_PACKER_H__

#include "network/message.h"

#include <cstdlib>

namespace wanderer
{
#define BUFFER_SIZE 1024 * 1024
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
    virtual size_t ToBytes(const T &message) = 0;

    // //转消息结构
    // Message *ToMessage(const char *buffer, int size) = 0;

    virtual char *Read() const = 0;

protected:
    char buffer_[BUFFER_SIZE];
    char *data_;
};

} // namespace wanderer

#endif