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

        //处理消息
        void OnMessageReceive(const Session *session, IMessage *message);

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
    };
} // namespace wanderer
#endif