#ifndef __EXPLAINC_MODULE_H__
#define __EXPLAINC_MODULE_H__

#include "base/module.h"

namespace wanderer
{
    class ExplainC : public Module
    {
    private:
        /* data */
    public:
        ExplainC(System *system);
        ~ExplainC();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;
    };
}

#endif