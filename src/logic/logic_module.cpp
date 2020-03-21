#include "logic/logic_module.h"

namespace wanderer
{
LogicModule::LogicModule(System *system) : Module(system)
{
}

LogicModule::~LogicModule()
{
}

//初始化函数
void LogicModule::OnInit()
{
    //inner_session_ = new InnerSession("127.0.0.1", 2233, "All");
}

//循环
void LogicModule::OnUpdate()
{
    //inner_session_->Loop();
}

//关闭
void LogicModule::OnClose()
{
    //  delete inner_session_;
}

} // namespace wanderer