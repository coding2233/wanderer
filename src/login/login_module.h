#ifndef __LOGIN_MODULE_H__
#define __LOGIN_MODULE_H__

#include <map>

#include "base/app_config.h"
#include "base/module.h"
#include "network/message.h"
#include "network/network_module.h"

namespace wanderer
{
    class LoginModule : public Module
    {
    private:
        /* data */
        // InnerSession *inner_session_;

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