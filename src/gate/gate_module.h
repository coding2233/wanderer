#ifndef __GATE_MODULE_H__
#define __GATE_MODULE_H__

#include <functional>

#include "base/module.h"
#include "network/network_module.h"

namespace wanderer
{
    class GateModule : public Module
    {
    private:
        /* data */
        // InnerSession *inner_session_;

        //处理消息
        void OnMessageReceive(const Session* session, IMessage* message);

    public:
        GateModule(System *system);
        ~GateModule();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;
    };
} // namespace wanderer
#endif