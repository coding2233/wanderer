#include "export.h"
#include "network.h"

#include <functional>
#include <iostream>

INITIALIZE_EASYLOGGINGPP

wanderer::Network network_;
WANDERER_CONNECT_CALLBACK connect_callback_cfunc_=NULL;
WANDERER_LOGIN_CALLBACK login_callback_cfunc_;

void OnConnectCallback(bool result, std::string messsage)
{
    std::cout << "export.cpp: --ConnectCallback result: "<<result<<" messsage: "<<messsage << std::endl;
    connect_callback_cfunc_(result, messsage.c_str());
}

void OnLoginCallback(bool result, std::string messsage)
{
    login_callback_cfunc_(result, messsage.c_str());
}

void WandererTest(const char *data)
{
    std::cout << "Test data:" << data << std::endl;
}

void WandererConnect(const char *server_ip, int server_port, WANDERER_CONNECT_CALLBACK connect_callback_c)
{
    std::cout << "server ip:" << server_ip << " server port:" << server_port << std::endl;
    connect_callback_cfunc_ = connect_callback_c;
    std::cout << "wanderer::Network_ address:" << &network_<<"  callback: "<<std::to_string(connect_callback_c==NULL) << std::endl;
    auto connect_callback = std::bind(&OnConnectCallback, std::placeholders::_1, std::placeholders::_2);
    network_.Connect(server_ip, server_port, connect_callback);
}

void WandererDisConnect()
{
    std::cout << "DisConnect" << std::endl;
    network_.DisConnect();
}

void WandererUpdate()
{
    network_.Update();
}

void SendToWanderer(const char *data, size_t size)
{
    // network_.Send(fd, data, *message)
    // network->Send(fd,)
}

void WandererLogin(const char *user_name, const char *password, WANDERER_LOGIN_CALLBACK login_callback_c)
{
    login_callback_cfunc_ = login_callback_c;
    auto login_callback = std::bind(&OnLoginCallback, std::placeholders::_1, std::placeholders::_2);
    network_.Login(user_name, password, login_callback);
}

// void Send(wanderer::Network &network, const char *data, size_t size)
// {
//     network.Send(data, size);
// }