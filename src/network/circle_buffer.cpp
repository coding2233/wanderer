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

        // if (size == 5)
        // {
        //     for (size_t i = 0; i < size; i++)
        //     {
        //         LOG(INFO) << "CircleBuffer::Write Before: " << std::to_string(data[i]) << "--" << std::to_string(buffer_[i]);
        //     }
        // }

        //暂时不考虑写满的情况
        std::memcpy(write_, data, size);
        write_ += size;
        length_ += size;

        // if (size == 5)
        // {
        //     for (size_t i = 0; i < size; i++)
        //     {
        //         LOG(INFO) << "CircleBuffer::Write After: " << std::to_string(data[i]) << "--" << std::to_string(buffer_[i]);
        //     }
        // }
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
            std::memcpy(temp_data + size, read_, length_);
            Flush();
        }
        Write((const char *)temp_data, data_size);
        LOG(INFO) << "Write header to int: " << CharPointer2Int(temp_data) << "  " << temp_data;
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
            LOG(FATAL) << "Pop size out of range!";
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