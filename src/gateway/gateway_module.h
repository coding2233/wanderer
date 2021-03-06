#ifndef __GATEWAY_MODULE_H__
#define __GATEWAY_MODULE_H__

#include <functional>

#include "base/module.h"
#include "network/network_module.h"

namespace wanderer
{
    class GatewayModule : public Module
    {
    private:
    public:
        GatewayModule(System *system);
        ~GatewayModule();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;
    };
} // namespace wanderer
#endif