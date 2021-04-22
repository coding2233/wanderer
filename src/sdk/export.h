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
    typedef void (*LOGIN_CALLBACK)(bool, const char *);

    void Test(const char *data);

    wanderer::Network *WANDERER_EXPORT Connect(const char *server_ip, int server_port, CONNECT_CALLBACK connect_callback);

    void WANDERER_EXPORT DisConnect(wanderer::Network *network);

    void WANDERER_EXPORT Update(wanderer::Network *network);

    void WANDERER_EXPORT Send(wanderer::Network *network, int fd, const char *data, size_t size);

    void WANDERER_EXPORT Login(wanderer::Network *network, const char *user_name, const char *password, LOGIN_CALLBACK login_callback);

#ifdef __cplusplus
}
#endif

#endif