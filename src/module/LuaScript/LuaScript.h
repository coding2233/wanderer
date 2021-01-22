#ifndef __LUA_SCRIPT_MODULE_H__
#define __LUA_SCRIPT_MODULE_H__

#include "LuaScript/lua-5.4.2/src/lapi.h"
#include "base/module.h"

namespace wanderer
{
    class LuaScript : public Module
    {
    private:
        /* data */
    public:
        LuaScript(System *system);
        ~LuaScript();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;
    };


} // namespace wanderer

#endif