#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__

#include <functional>
#include <queue>

#include "base/easylogging++.h"

namespace wanderer
{

#define BUFFER_MAX_SIZE 1024

    class SocketBase
    {
    private:
        /* data */

    public:
        SocketBase(/* args */);
        virtual ~SocketBase();

        //设置
        virtual void Setup(std::function<void(int)> connected_callback, std::function<void(int, const char *data, int size)> receive_callback, std::function<void(const char name, int fd)> inner_connected_callback);
        //循环
        virtual void Loop() = 0;
        //关闭
        virtual void Close() = 0;
        //发送数据
        virtual int SendData(int fd, const char *data, size_t size) = 0;
        //创建监听socket
        virtual int CreateListenSocket(const char *server_ip, int server_port);
        //创建客户端的socket
        virtual void CreateConnectSocket(const char name, const char *server_ip, int server_port);

    protected:
        //缓存数据
        char buffer_[BUFFER_MAX_SIZE];
        //连接回调
        std::function<void(int)> connected_callback_;
        //数据接收回调
        std::function<void(int, const char *data, int size)> receive_callback_;
        //内部通信创建回调
        std::function<void(const char name, int fd)> inner_connected_callback_;
        //显示logo
        virtual void SetLogo() = 0;
    };
} // namespace wanderer

#endif