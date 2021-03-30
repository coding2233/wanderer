#ifndef __CENTER_MODULE_H__
#define __CENTER_MODULE_H__

#include <functional>

#include "base/module.h"
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
    };
} // namespace wanderer
#endif