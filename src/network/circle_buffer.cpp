#include "network/circle_buffer.h"

namespace wanderer
{

CircleBuffer::CircleBuffer(/* args */)
{
    read_ = buffer_;
    write_ = buffer_;
}

CircleBuffer::~CircleBuffer()
{
    delete read_;
    delete write_;
}

void CircleBuffer::Write(const char *data, int size)
{
    //暂时不考虑写满的情况
    memcpy(write_, data, size);
    write_ += size;
    length_ += size;
}

char *CircleBuffer::Read() const
{
    return read_;
}

void CircleBuffer::Flush(int size)
{
    if (size > length_)
    {
        throw std::runtime_error("pop size out of range");
    }

    length_ -= size;
    memmove(read_, read_ + size, length_);
    write_ -= size;
    memset(write_, length_, CIRCLE_BUFFER_SIZE - length_);
}

int CircleBuffer::Length()
{
    return length_;
}

} // namespace wanderer