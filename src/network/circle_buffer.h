#ifndef __CIRCLE_BUFFER_H__
#define __CIRCLE_BUFFER_H__

#include <cstring>
#include <stdexcept>

#include "base/easylogging++.h"
#include "utility/utility.h"

namespace wanderer
{

//1MB
#define CIRCLE_BUFFER_SIZE 1024 * 1024

    class CircleBuffer
    {
    private:
        /* data */
        char buffer_[CIRCLE_BUFFER_SIZE];
        //读取指针
        char *read_;
        //写入指针
        char *write_;
        //长度
        int length_;

    public:
        CircleBuffer(/* args */);
        ~CircleBuffer();

        //写进来的数据
        void Write(const char *data, int size);

        //写入数据
        void Write(const char data);

        //写入数据的大小
        void WriteHeader(const char type);

        //读取数据
        char *Read() const;

        //清理数据
        void Flush(int size);

        //清理数据
        void Flush();

        //数据长度
        int Length();
    };
} // namespace wanderer
#endif