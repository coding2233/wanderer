//https://blog.csdn.net/x356982611/article/details/26688287
//https://blog.csdn.net/shun_fzll/article/details/39120965

#ifndef __LUA_SCRIPT_MODULE_H__
#define __LUA_SCRIPT_MODULE_H__

#include <iostream>

extern "C"
{
#include "lua/lauxlib.h"
#include "lua/lua.h"
#include "lua/lualib.h"
}

#include "actor/actor_module.h"
#include "actor_lua.h"
#include "base/module.h"

namespace wanderer
{
    class LuaScript : public Module
    {
    private:
        /* lua_State */
        lua_State *global_state_ = nullptr;
        //Registering C functions
        void RegisterCFunction();
        //Set the search Lua file folder
        void SetLuaSearchPath();

    public:
        LuaScript(System *system);
        ~LuaScript();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;

        // static int RegisterActor(lua_State *pL);
    };

} // namespace wanderer

#endif