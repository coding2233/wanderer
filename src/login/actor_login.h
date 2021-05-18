#ifndef __ACTOR_LOGIN_H__
#define __ACTOR_LOGIN_H__

#include "actor/actor.h"

namespace wanderer
{
    class ActorLogin : public Actor
    {
    private:
        /* data */
    protected:
        void MailHandler(Mail mail) override;

    public:
        ActorLogin(/* args */);
        ~ActorLogin();
    };

} // namespace wanderer

#endif