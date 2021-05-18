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
        if (app_type == AppType_Login)
        {
            forward_address_[ActorAddress_LOGIN] = address;
        }
        else if (app_type == AppType_DataBase)
        {
            forward_address_[ActorAddress_DATABASE] = address;
        }
    }

    int CenterModule::ForwardAddress(int address)
    {
        auto iter = forward_address_.find(address);
        if (iter != forward_address_.end())
        {
            return iter->second;
        }
        return address;
    }

} // namespace wanderer