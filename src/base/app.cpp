#include "base/app.h"

namespace wanderer
{

App::App()
{
}

App::~App()
{
}

void App::Run(int argc, char *args[])
{
    InitModule();
    Init();
    MainLoop();
    CleanUp();
}

// Module *App::GetModule(const std::string &name)
// {
//     module_iter_ = modules_.find(name);
//     if (module_iter_ != modules_.end())
//     {
//         return module_iter_->second;
//     }
//     return nullptr;
// }

void App::InitModule()
{
    //添加network模块
    modules_.insert(std::pair<std::string, Module *>("network", new NetworkModule()));
    modules_.insert(std::pair<std::string, Module *>("logic", new LogicModule()));
}

void App::Init()
{
    //遍历
    for (module_iter_ = modules_.begin(); module_iter_ != modules_.end(); module_iter_++)
    {
        module_iter_->second->OnInit();
    }
}

void App::MainLoop()
{
    while (1)
    {
        for (module_iter_ = modules_.begin(); module_iter_ != modules_.end(); module_iter_++)
        {
            module_iter_->second->OnUpdate();
        }
    }
}

void App::CleanUp()
{
    for (module_iter_ = modules_.begin(); module_iter_ != modules_.end(); module_iter_++)
    {
        Module *module = module_iter_->second;
        module->OnClose();
        delete module;
    }
    modules_.clear();
}
} // namespace wanderer