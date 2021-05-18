#ifndef __CENTER_MODULE_H__
#define __CENTER_MODULE_H__

#include <functional>

#include "actor/actor_module.h"
#include "base/module.h"
#include "center/actor_center.h"
#include "network/network_module.h"

namespace wanderer
{
    class CenterModule : public Module
    {
    private:
        /* data */
        // InnerSession *inner_session_;
        std::map<int, int> forward_address_;

    public:
        CenterModule(System *system);
        ~CenterModule();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;

        void AppAuth(AppType_ app_type, int address);

        int ForwardAddress(int address);
    };
} // namespace wanderer
#endif