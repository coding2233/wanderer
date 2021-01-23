#ifndef __GATE_MODULE_H__
#define __GATE_MODULE_H__

#include "base/module.h"

namespace wanderer
{
    class GateModule : public Module
    {
    private:
        /* data */
        // InnerSession *inner_session_;

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