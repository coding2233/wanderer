#include "center/actor_auth.h"
#include "actor/actor.h"

namespace wanderer
{
    ActorAuth::ActorAuth()
    {
    }

    ActorAuth::~ActorAuth()
    {
    }

    void ActorAuth::MailHandler(Mail mail)
    {
        LOG(DEBUG) << "ActorAuth::MailHandler(Mail mail): " << mail.from_address_;
    }

}