#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <iostream>
#include <map>

#include "socket_client_base.h"
#if WIN32
#include "socket_windows.h"
#elif __unix__
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
        int gateway_fd_;

        bool login_connected_ = false;

        std::string gateway_key_;

        void OnReceive(int fd, const char *data, size_t size);
        void OnYAMLReceive(int fd, YAML::Node message);
        std::string CreateSecretKey();

    public:
        Network(/* args */);
        ~Network();

        int Connect(const char *server_ip, int server_port);

        void DisConnect();

        void Send(int fd, IMessage *message);

        void Update();

        void Login(const char *user_name, const char *password);
    };
}

#endif