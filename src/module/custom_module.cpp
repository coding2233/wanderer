//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!

#include "custom_module.h"
#if LUASCRIPT
#include "LuaScript/LuaScript.h"
#endif

namespace wanderer
{
CustomModule::CustomModule(std::map<std::string, Module *> *modules, System *system)
{

#if LUASCRIPT
	LuaScript *luascript__ = new LuaScript(system);
	modules->insert(std::pair<std::string, Module *>(typeid(*luascript__).name(),luascript__));
#endif

}

CustomModule::~CustomModule()
{
}
}
