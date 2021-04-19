#ifndef __EXPORT_H__
#define __EXPORT_H__

#include "network.h"
#include <iostream>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif

#if WIN32
// #define WANDERER_EXPORT _declspec(dllexport) _cdecl
#define WANDERER_EXPORT
#elif unix
#define WANDERER_EXPORT
#endif

    typedef void (*RECEIVE_FUNC)(int, const char *, int);

    void Test(const char *data);

    wanderer::Network *WANDERER_EXPORT Connect(const char *server_ip, int server_port, RECEIVE_FUNC receive_callback);

    void WANDERER_EXPORT DisConnect(wanderer::Network *network);

    void WANDERER_EXPORT Update(wanderer::Network *network);

    void WANDERER_EXPORT Send(wanderer::Network *network, int fd, const char *data, size_t size);
#ifdef __cplusplus
}
#endif

#endif