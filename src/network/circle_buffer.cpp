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
            LOG(FATAL) << "Data write out of cache.";
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
        int data_size = length_ + size;
        char *temp_data = new char[data_size];
        Int2CharPointer(temp_data, data_size);
        temp_data[4] = type;
        if (length_ > 0)
        {
            std::memcpy(temp_data + 5, read_, length_);
            Flush();
        }
        Write(temp_data, data_size);

        delete[] temp_data;
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