#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <map>

#if WIN32
#include "socket_windows.h"
#elif unix
#include "socket_unix.h"
#endif

#include "network/circle_buffer.h"
#include "network/message.h"
#include "utility/openssl_utility.h"
#include "utility/utility.h"

namespace wanderer
{
    struct SessionData
    {
        std::string buffer_;
        std::string secret_key_;
    };

    class Network
    {
    private:
        /* data */
        SocketClientBase *socket_;

        std::map<int, SessionData *> sessions_;

        int login_fd_;

    protected:
        void OnReceive(int fd, const char *data, size_t size);

        std::string CreateSecretKey();

    public:
        Network(/* args */);
        ~Network();

        void Connect(const char *server_ip, int server_port, void *receive_callback, void *connect_faile);

        void DisConnect();

        void Send(int fd, const char *dta, size_t size);

        void Update();

        void Login(const char *user_name, const char *password);
    };
}

#endif