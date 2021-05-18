#include "center/center_module.h"

namespace wanderer
{
    CenterModule::CenterModule(System *system) : Module(system)
    {
    }

    CenterModule::~CenterModule()
    {
    }

    //初始化函数
    void CenterModule::OnInit()
    {
        GetSystem()->GetModule<ActorModule>()->Register(new ActorCenter, ActorAddress_CENTER);
    }

    //循环
    void CenterModule::OnUpdate()
    {
    }

    //关闭
    void CenterModule::OnClose()
    {
    }

    void CenterModule::AppAuth(AppType_ app_type, int address)
    {
    }

} // namespace wanderer