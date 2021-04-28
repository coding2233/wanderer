#ifndef __EXPORT_H__
#define __EXPORT_H__

#include "network.h"
#include <iostream>
#include <string>

// #ifdef __cplusplus
// extern "C"
// {
// #endif

#if WIN32
#include "windows.h"
// _declspec(dllexport) _cdecl
#define WANDERER_EXPORT extern "C" _declspec(dllexport)
#elif unix
#define WANDERER_EXPORT extern "C"
#endif

    typedef void (*RECEIVE_FUNC)(int, const char *, int);
    typedef void (*LOGIN_CALLBACK)(bool, const char *);

    WANDERER_EXPORT void Test(const char *data);

    WANDERER_EXPORT wanderer::Network *NewNetwork();

    WANDERER_EXPORT void DeleteNetwork(wanderer::Network * network);

    WANDERER_EXPORT void Connect(wanderer::Network * network,const char *server_ip, int server_port);

    WANDERER_EXPORT void DisConnect(wanderer::Network *network);

    WANDERER_EXPORT void Update(wanderer::Network *network);

    WANDERER_EXPORT void Send(wanderer::Network *network, int fd, const char *data, size_t size);

    WANDERER_EXPORT void Login(wanderer::Network *network, const char *user_name, const char *password, LOGIN_CALLBACK login_callback);

// #ifdef __cplusplus
// }
// #endif

#endif