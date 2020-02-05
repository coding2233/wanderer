#ifndef __NETWORKMODULE_H__
#define __NETWORKMODULE_H__

#include "base/module.h"
#include "network/socket_epoll.h"

#define SERVER_PORT 2233

class NetworkModule : public Module
{
private:
    SocketEpoll *socket_epoll_;

public:
    NetworkModule(
        /* args */);
    ~NetworkModule();
    //初始化函数
    void OnInit() override;

    void OnUpdate() override;

    void OnClose() override;
};

#ifdef __cplusplus
extern "C"
{
#endif
    void *CreateNetworkModule();

#ifdef __cplusplus
}
#endif

#endif