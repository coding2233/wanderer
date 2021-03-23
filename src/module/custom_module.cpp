//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!

#include "custom_module.h"
#if WEBSERVER
#include "WebServer/WebServer.h"
#endif

namespace wanderer
{
CustomModule::CustomModule(std::map<std::string, Module *> *modules, System *system)
{

#if WEBSERVER
	WebServer *webserver__ = new WebServer(system);
	modules->insert(std::pair<std::string, Module *>(typeid(*webserver__).name(),webserver__));
#endif

}

CustomModule::~CustomModule()
{
}
}
