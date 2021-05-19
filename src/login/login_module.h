#ifndef __LOGIN_MODULE_H__
#define __LOGIN_MODULE_H__

#include <map>
#include <string>

#include "actor/actor_module.h"
#include "base/app_config.h"
#include "base/module.h"
#include "login/actor_login.h"
#include "network/message.h"
#include "network/network_module.h"
#include "utility/jsonrpcpp.hpp"

namespace wanderer
{
    class LoginModule : public Module
    {
    private:
        /* data */

    public:
        LoginModule(System *system);
        ~LoginModule();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;
    };
} // namespace wanderer
#endif