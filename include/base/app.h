#ifndef __APP_H__
#define __APP_H__

#include "base/module.h"
#include "network/network_module.h"

#include <iostream>
#include <map>

class App
{
private:
    static std::map<std::string, Module *> modules_;
    static std::map<std::string, Module *>::iterator module_iter_;

private:
    //初始化模块
    void InitModule();
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
    void Run(int argc, char *args[]);
    //获取模块
    static Module *GetModule(const std::string &name);
};

#endif
