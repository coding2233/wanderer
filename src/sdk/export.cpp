#include "export.h"
#include <iostream>


wanderer::Network network_;

void Test(const char *data)
{
    std::cout << "Test data:" << data << std::endl;
}

void Connect(const char *server_ip, int server_port)
{
    std::cout << "server ip:" << server_ip << " server port:" << server_port << std::endl;

    std::cout<<"wanderer::Network_ address:"<<&network_<<std::endl;
   
    network_.Connect(server_ip, server_port);
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

void Login(const char *user_name, const char *password, LOGIN_CALLBACK login_callback)
{
    network_.Login(user_name, password);
}

// void Send(wanderer::Network &network, const char *data, size_t size)
// {
//     network.Send(data, size);
// }