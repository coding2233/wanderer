#include "export.h"
#include "network.h"

#include <functional>
#include <iostream>

INITIALIZE_EASYLOGGINGPP

wanderer::Network network_;
CONNECT_CALLBACK_CFUNC connect_callback_cfunc_;
LOGIN_CALLBACK_CFUNC login_callback_cfunc_;

void Test(const char *data)
{
    std::cout << "Test data:" << data << std::endl;
}

void Connect(const char *server_ip, int server_port, CONNECT_CALLBACK_CFUNC connect_callback_c)
{
    std::cout << "server ip:" << server_ip << " server port:" << server_port << std::endl;

    std::cout << "wanderer::Network_ address:" << &network_ << std::endl;
    connect_callback_cfunc_ = connect_callback_c;
    auto connect_callback = std::bind(&ConnectCallback, std::placeholders::_1, std::placeholders::_2);
    network_.Connect(server_ip, server_port, connect_callback);
}

void ConnectCallback(bool result, std::string messsage)
{
    std::cout << "export.cpp: --ConnectCallback " << std::endl;
    connect_callback_cfunc_(result, messsage.c_str());
}

void DisConnect()
{
    std::cout << "DisConnect" << std::endl;
    network_.DisConnect();
}

void Update()
{
    network_.Update();
}

void Send(int fd, const char *data, size_t size)
{
    // network_.Send(fd, data, *message)
    // network->Send(fd,)
}

void Login(const char *user_name, const char *password, LOGIN_CALLBACK_CFUNC login_callback_c)
{
    login_callback_cfunc_ = login_callback_c;
    auto login_callback = std::bind(&ConnectCallback, std::placeholders::_1, std::placeholders::_2);
    network_.Login(user_name, password, login_callback);
}

void LoginCallback(bool result, std::string messsage)
{
    login_callback_cfunc_(result, messsage.c_str());
}

// void Send(wanderer::Network &network, const char *data, size_t size)
// {
//     network.Send(data, size);
// }