#ifndef __LOGIC_MODULE_H__
#define __LOGIC_MODULE_H__

#include "base/module.h"
#include "logic/inner_session.h"

namespace wanderer
{
class LogicModule : public Module
{
private:
    /* data */
    InnerSession *inner_session_;

public:
    LogicModule(/* args */);
    ~LogicModule();

    //初始化函数
    void OnInit() override;
    //循环
    void OnUpdate() override;
    //关闭
    void OnClose() override;
};
} // namespace wanderer
#endif