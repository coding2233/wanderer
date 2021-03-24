//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!

#include "custom_module.h"
#if LUASCRIPT
#include "LuaScript/LuaScript.h"
#endif
#if WEBSERVER
#include "WebServer/WebServer.h"
#endif

namespace wanderer
{
CustomModule::CustomModule(std::map<std::string, Module *> *modules, System *system)
{

#if LUASCRIPT
	LuaScript *luascript__ = new LuaScript(system);
	modules->insert(std::pair<std::string, Module *>(typeid(*luascript__).name(),luascript__));
#endif


#if WEBSERVER
	WebServer *webserver__ = new WebServer(system);
	modules->insert(std::pair<std::string, Module *>(typeid(*webserver__).name(),webserver__));
#endif

}

CustomModule::~CustomModule()
{
}
}
