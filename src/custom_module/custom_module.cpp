//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!
//This file is generated automatically by the program and is not allowed to be modified manually!

#include "custom_module/custom_module.h"

CustomModule::CustomModule(std::map<std::string, Module *> *modules, System *system)
{

#if TEST
	test *test__ = new test(system);
	modules.insert(std::pair<std::string, Module *>(typeid(*test__).name(), test__));
#endif
}

CustomModule::~CustomModule()
{
}
