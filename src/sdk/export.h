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
#if BUILD_SDK
#define WANDERER_EXPORT extern "C" _declspec(dllexport)
#else
#define WANDERER_EXPORT extern "C" _declspec(dllimport)
#endif
#elif __unix__ || __APPLE__
#define WANDERER_EXPORT extern "C"
#endif

typedef void (*RECEIVE_FUNC)(int, const char *, int);
typedef void (*CONNECT_CALLBACK_CFUNC)(bool, const char *);
typedef void (*LOGIN_CALLBACK_CFUNC)(bool, const char *);
// typedef void (*LOGIN_CALLBACK)(bool, const char *);

WANDERER_EXPORT void Test(const char *data);

WANDERER_EXPORT void Connect(const char *server_ip, int server_port, CONNECT_CALLBACK_CFUNC connect_callback);

void ConnectCallback(bool result, std::string messsage);

WANDERER_EXPORT void DisConnect();

WANDERER_EXPORT void Update();

WANDERER_EXPORT void Send(int fd, const char *data, size_t size);

WANDERER_EXPORT void Login(const char *user_name, const char *password, LOGIN_CALLBACK_CFUNC login_callback);

void LoginCallback(bool result, std::string messsage);

// #ifdef __cplusplus
// }
// #endif

#endif