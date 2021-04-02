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
        if (length_ + size >= CIRCLE_BUFFER_SIZE)
        {
            throw std::runtime_error("Data write out of cache.");
        }

        //暂时不考虑写满的情况
        memcpy(write_, data, size);
        write_ += size;
        length_ += size;
    }

    void CircleBuffer::Write(const char data)
    {
        Write(&data, 1);
    }

    void CircleBuffer::WriteHeader(const char type)
    {
        int size = 5;
        char data_size[size];
        Int2CharPointer(data_size, length_ + 5);
        data_size[4] = type;
        memmove(buffer_ + size, buffer_, length_);
        write_ += size;
        length_ += size;
        memcpy(buffer_, data_size, size);
        // memcpy(read_ + 4, read_, length_);
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
        // read_ = buffer_;
    }

    void CircleBuffer::Flush()
    {
        Flush(length_);
    }

    int CircleBuffer::Length()
    {
        return length_;
    }

} // namespace wanderer