#ifndef __ACTOR_INNER_H__
#define __ACTOR_INNER_H__

#include "actor/actor.h"

namespace wanderer 
{
    class ActorInner:public Actor
    {
    public: 
        ActorInner(int address);
        ~ActorInner();
    };
}


#endif