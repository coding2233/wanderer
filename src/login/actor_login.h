#ifndef __ACTOR_LOGIN_H__
#define __ACTOR_LOGIN_H__

#include <map>

#include "actor/actor.h"

namespace wanderer
{
    class ActorLogin : public Actor
    {
    private:
        /* data */
        std::map<std::string, int> login_response;

    protected:
        void OnMailHandle(Mail mail) override;

    public:
        ActorLogin(/* args */);
        ~ActorLogin();
    };

} // namespace wanderer

#endif