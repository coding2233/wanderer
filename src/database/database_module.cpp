#include "database_module.h"
namespace wanderer
{
    DatabaseModule::DatabaseModule(System *system) : Module(system)
    {
    }

    DatabaseModule::~DatabaseModule()
    {
    }

    //初始化函数
    void DatabaseModule::OnInit()
    {
        GetSystem()->GetModule<ActorModule>()->Register(new ActorDatabase, ActorAddress_DATABASE);
    }

    //循环
    void DatabaseModule::OnUpdate()
    {
    }

    //关闭
    void DatabaseModule::OnClose()
    {
    }
}