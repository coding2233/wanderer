#ifndef __WANDERER_EXPORT_H__
#define __WANDERER_EXPORT_H__

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

// typedef void (*WANDERER_RECEIVE)(int, const char *, int);
typedef void (*WANDERER_CONNECT_CALLBACK)(bool, const char *);
typedef void (*WANDERER_LOGIN_CALLBACK)(bool, const char *);
// typedef void (*LOGIN_CALLBACK)(bool, const char *);

WANDERER_EXPORT void WandererTest(const char *data);

WANDERER_EXPORT void WandererConnect(const char *server_ip, int server_port, WANDERER_CONNECT_CALLBACK connect_callback);

WANDERER_EXPORT void WandererDisConnect();

WANDERER_EXPORT void WandererUpdate();

WANDERER_EXPORT void SendToWanderer(int fd, const char *data, size_t size);

WANDERER_EXPORT void WandererLogin(const char *user_name, const char *password, WANDERER_LOGIN_CALLBACK login_callback);

// #ifdef __cplusplus
// }
// #endif

#endif