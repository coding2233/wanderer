#ifndef __APP_H__
#define __APP_H__

#include <csignal>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "base/app_config.h"
#include "base/easylogging++.h"
#include "base/module.h"
#include "base/system.h"
#include "center/center_module.h"
#include "gateway/gateway_module.h"
#include "inner_session/inner_session_module.h"
#include "login/login_module.h"
#include "module/custom_module.h"
#include "network/network_module.h"
#include "actor/actor_module.h"

namespace wanderer
{

    class App
    {
    private:
        std::map<std::string, Module *> modules_;
        std::map<std::string, Module *>::iterator module_iter_;

        System *system_;
        static int signal_flag_;

    private:
        //初始化模块
        void InitModule(AppConfig *app_config);
        //初始化
        void Init();
        //循环
        void MainLoop();
        //清理
        void CleanUp();
        //添加模块
        void AddModule(Module *module);

        //信号处理
        static void SignalHandler(int signal)
        {
            signal_flag_ = signal;
        }

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
