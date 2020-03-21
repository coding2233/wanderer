#include "base/module.h"
namespace wanderer
{

Module::Module(System *system)
{
    system_ = system;
}

Module::~Module()
{
}

void Module::OnInit()
{
}

void Module::OnUpdate()
{
}

void Module::OnClose()
{
}

System *Module::GetSystem() const
{
    return system_;
}

} // namespace wanderer