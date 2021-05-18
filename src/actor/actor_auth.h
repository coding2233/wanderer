#ifndef __ACTOR_AUTH_H__
#define __ACTOR_AUTH_H__

#include "actor/actor.h"
#include "base/easylogging++.h"

namespace wanderer
{
    class ActorAuth : public Actor
    {
    protected:
        void MailHandler(Mail mail) override;

    public:
        ActorAuth();
        ~ActorAuth();
    };
}

#endif