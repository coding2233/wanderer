#ifndef __APP_H__
#define __APP_H__

#include "socket/socket_epoll.h"

#include <iostream>

#define SERVER_PORT 2233

class App
{
private:
    SocketEpoll *socket_epoll_;

private:
    //初始化
    void Init();
    //循环
    void MainLoop();
    //清理
    void CleanUp();

public:
    App(/* args */);
    ~App();
    //运行
    void Run();
};

#endif
