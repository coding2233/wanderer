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
        GetSystem()->GetModule<ActorModule>()->Register(new ActorAuth, ActorAddress_CENTER_AUTH);
        // GetSystem()->GetModule<ActorModule>()->SpawnActor<ActorInner>(ActorAddress_CENTER_AUTH);
    }

    //循环
    void CenterModule::OnUpdate()
    {
    }

    //关闭
    void CenterModule::OnClose()
    {
    }

} // namespace wanderer