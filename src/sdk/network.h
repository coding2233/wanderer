#ifndef __NETWORK_H__
#define __NETWORK_H__

#include <functional>
#include <iostream>
#include <map>

#include "socket_client_base.h"
#if unix
#include "socket_unix.h"
#elif WIN32
#include "socket_windows.h"
#endif

#include "actor/actor.h"
#include "network/circle_buffer.h"
#include "network/message.h"
#include "utility/jsonrpcpp.hpp"
#include "utility/openssl_utility.h"
#include "utility/utility.h"

namespace wanderer
{

#define CONNECT_CALLBACK std::function<void(bool, std::string)>
#define LOGIN_CALLBACK std::function<void(bool, std::string)>

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
        jsonrpcpp::Parser jsonrpc_parser_;
        int request_index_;
        int login_fd_;
        int gateway_fd_;

        bool login_connected_;
        bool gateway_connected_;

        int login_address_;
        int gateway_address_;

        std::string gateway_key_;

        CONNECT_CALLBACK connect_callback_;
        LOGIN_CALLBACK login_callback_;

        void OnReceive(int fd, const char *data, size_t size);
        void OnJsonRpcReceive(int fd, jsonrpcpp::entity_ptr entity);
        std::string CreateSecretKey();

        int ConnectGateway(const char *server_ip, int server_port);

    public:
        Network(/* args */);
        ~Network();

        int Connect(const char *server_ip, int server_port, CONNECT_CALLBACK connect_callback);

        void DisConnect();

        void Send(int fd, IMessage *message);

        void Update();

        void Login(const char *user_name, const char *password, LOGIN_CALLBACK login_callback);
    };
}

#endif