#include "actor_lua.h"

namespace wanderer
{
    ActorLua::ActorLua(/* args */) : Actor()
    {
    }

    ActorLua::~ActorLua()
    {
    }

    void ActorLua::OnMailHandle(Mail mail)
    {
        System::GetModule<LuaScript>()->HandleMail(mail);
    }
}