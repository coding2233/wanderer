#ifndef __ACTOR_INNER_H__
#define __ACTOR_INNER_H__

#include "actor/actor.h"
#include "base/easylogging++.h"

namespace wanderer
{
    class ActorInner : public Actor
    {
    protected:
        void MailHandler(Mail mail) override;

    public:
        ActorInner();
        ~ActorInner();
    };
}

#endif