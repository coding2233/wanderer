#include "export.h"

void Test(const char *data)
{
    std::cout << "Test data:" << data << std::endl;
}

wanderer::Network *Connect(const char *server_ip, int server_port, CONNECT_CALLBACK connect_callback)
{
    std::cout << "server ip:" << server_ip << " server port:" << server_port << std::endl;
    wanderer::Network *network = new wanderer::Network();
    network->Connect(server_ip, server_port);
    return network;
}

void DisConnect(wanderer::Network *network)
{
    std::cout << "DisConnect" << std::endl;
    network->DisConnect();
    delete network;
}

void Update(wanderer::Network *network)
{
    network->Update();
}

void Send(wanderer::Network *network, int fd, const char *data, size_t size)
{
    // network->Send(fd,)
}

void Login(wanderer::Network *network, const char *user_name, const char *password, LOGIN_CALLBACK login_callback)
{
    network->Login(user_name, password);
}

// void Send(wanderer::Network &network, const char *data, size_t size)
// {
//     network.Send(data, size);
// }