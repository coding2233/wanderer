#include "base/app.h"

App::App()
{
}

App::~App()
{
}

void App::Run()
{
    Init();
    MainLoop();
    CleanUp();
}

void App::Init()
{
    socket_epoll_ = new SocketEpoll;
    socket_epoll_->Setup(SERVER_PORT);
}

void App::MainLoop()
{
    while (1)
    {
        socket_epoll_->Loop();
    }
}

void App::CleanUp()
{
    socket_epoll_->Close();
    free(socket_epoll_);
}
