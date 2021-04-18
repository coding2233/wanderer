#include "export.h"

void Test(const char *data)
{
    std::cout << "Test data:" << data << std::endl;
}

wanderer::Network *Connect(const char *server_ip, int server_port, RECEIVE_FUNC receive_callback)
{
    if (receive_callback != nullptr)
    {
        const char *data = "sdsafsd";
        receive_callback(0, data, 2);
        // delete data;
    }

    std::cout << "server ip:" << server_ip << " server port:" << server_port << std::endl;
    wanderer::Network *network = new wanderer::Network();
    network->Connect(server_ip, server_port, nullptr, nullptr);
    return network;
}

void DisConnect(wanderer::Network *network)
{
    std::cout << "DisConnect" << std::endl;
    network->DisConnect();
    delete network;
}

void WANDERER_EXPORT Update(wanderer::Network *network)
{
    network->Update();
}

void WANDERER_EXPORT Send(wanderer::Network *network, int fd, const char *data, size_t size)
{
    // network->Send(fd,)
}
// void Send(wanderer::Network &network, const char *data, size_t size)
// {
//     network.Send(data, size);
// }