#include "base/system.h"

namespace wanderer
{

std::map<std::string, Module *> *System::modules_=0;
AppConfig* System::app_config_ = nullptr;

System::System(std::map<std::string, Module *> *modules)
{
    modules_ = modules;
}

System::~System()
{
}
} // namespace wanderer
