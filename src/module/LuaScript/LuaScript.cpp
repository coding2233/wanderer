#include "LuaScript/LuaScript.h"

namespace wanderer
{
	LuaScript::LuaScript(System *system) : Module(system)
	{
	}

	LuaScript::~LuaScript()
	{
	}

	//初始化函数
	void LuaScript::OnInit()
	{
		global_state_ = luaL_newstate();
		//Load the Lua base library
		luaL_openlibs(global_state_);
		//Registering C functions
		RegisterCFunction();
		//Set the search Lua file folder
		SetLuaSearchPath();

		// luaL_dofile(global_state_, "main.lua");

		/*int num = luaL_dostring(global_state_, R"(print(package.path))");
		std::cout << "Luascript OnInit!  do lua num: " << num << std::endl;*/
	}

	//循环
	void LuaScript::OnUpdate()
	{
	}

	//关闭
	void LuaScript::OnClose()
	{
		lua_close(global_state_);
	}

	void LuaScript::RegisterCFunction()
	{
		/*lua_pushcfunction(global_state_, fn);
		lua_setglobal(global_state_, fn)*/
		//lua_register(global_state_, "xx", fn);
	}

	void LuaScript::SetLuaSearchPath()
	{
		//package.cpath
		//package.path
	}

} // namespace wanderer