#include "LuaScript/LuaScript.h"

namespace wanderer
{
	int RegisterActor(lua_State *pL)
	{
		int address = lua_tonumber(pL, -1);
		System::GetModule<ActorModule>()->Register(new ActorLua, address);
		LOG(INFO) << "int RegisterActor(lua_State *pL)";
		return 0;
	}

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
		luaL_dostring(global_state_, R"(require "main")");

		//获取lua中的showinfo函数
		lua_getglobal(global_state_, "OnRegisterActors");
		lua_pushinteger(global_state_, GetSystem()->app_config_->app_type_);
		//cpp 调用无参数的lua函数，无返回值
		lua_pcall(global_state_, 1, 0, 0);
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

		lua_register(global_state_, "RegisterActor", RegisterActor);
	}

	void LuaScript::SetLuaSearchPath()
	{
		luaL_dostring(global_state_, R"(package.path="./lua-src/?.lua;../lua-src/?.lua;./lua-libs/?.lua;../lua-libs/?.lua;"..package.path)");
		luaL_dostring(global_state_, R"(package.cpath="./lua-libs/?.so;../lua-libs/?.so;"..package.cpath)");
	}

} // namespace wanderer