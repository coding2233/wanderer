#ifndef __EXPORT_H__
#define __EXPORT_H__

#include <iostream>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif

    static void Connect(std::string server_ip, int server_port, void *receive_callback, void *connect_faile);

    static void DisConnect();

    static void Send(const char *data, size_t size);

#ifdef __cplusplus
}
#endif

#endif