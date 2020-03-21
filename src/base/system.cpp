#include "base/system.h"

namespace wanderer
{
System::System(std::map<std::string, Module *> *modules)
{
    modules_ = modules;
}

System::~System()
{
}
} // namespace wanderer