#ifndef __ACTOR_LUA_H__
#define __ACTOR_LUA_H__

#include "LuaScript.h"
#include "actor/actor.h"
#include "base/system.h"

namespace wanderer
{
    class ActorLua : public Actor
    {
    private:
        /* data */
    public:
        ActorLua(/* args */);
        ~ActorLua();

    protected:
        void OnMailHandle(Mail mail) override;
    };

}

#endif