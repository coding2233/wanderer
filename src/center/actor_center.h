#ifndef __ACTOR_CENTER_H__
#define __ACTOR_CENTER_H__

#include <iostream>

#include "actor/actor.h"
#include "base/easylogging++.h"
#include "center/center_module.h"

namespace wanderer
{
    class ActorCenter : public Actor
    {
    protected:
        void OnMailHandle(Mail mail) override;

    public:
        ActorCenter();
        ~ActorCenter();
    };
}

#endif