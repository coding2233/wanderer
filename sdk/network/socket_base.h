#ifndef __SOCKET_BASE_H__
#define __SOCKET_BASE_H__

namespace wanderer
{
    class SocketBase
    {
    private:
        /* data */
    public:
        SocketBase(/* args */);
        ~SocketBase();

        void Connect(std::string server_ip, int server_port) = 0;
    };
}
#endif