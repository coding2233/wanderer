#ifndef __APP_H__
#define __APP_H__

#include "base/system.h"
#include "base/module.h"
#include "network/network_module.h"
#include "logic/logic_module.h"
#include "base/app_config.h"

#include <iostream>
#include <map>
#include <string>

namespace wanderer
{
class App
{
private:
    std::map<std::string, Module *> modules_;
    std::map<std::string, Module *>::iterator module_iter_;

    System *system_;

private:
    //初始化模块
    void
    InitModule(AppConfig *app_config);
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
    //Module *GetModule(const std::string &name);
};
} // namespace wanderer
#endif
