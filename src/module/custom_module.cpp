//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!

#include "custom_module.h"
#if EXPLAINC
#include "ExplainC/ExplainC.h"
#endif
#if LUASCRIPT
#include "LuaScript/LuaScript.h"
#endif

namespace wanderer
{
CustomModule::CustomModule(std::map<std::string, Module *> *modules, System *system)
{

#if EXPLAINC
	ExplainC *explainc__ = new ExplainC(system);
	modules->insert(std::pair<std::string, Module *>(typeid(*explainc__).name(),explainc__));
#endif


#if LUASCRIPT
	LuaScript *luascript__ = new LuaScript(system);
	modules->insert(std::pair<std::string, Module *>(typeid(*luascript__).name(),luascript__));
#endif

}

CustomModule::~CustomModule()
{
}
}
