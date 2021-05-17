#include "center/actor_auth.h"
#include "actor/actor.h"

namespace wanderer 
{
    ActorAuth::ActorAuth(int address):Actor(address)
    {
    }


    ActorAuth::~ActorAuth()
    {

    }

    void ActorAuth::MailHandler(Mail mail)
    {
        std::cout<<"xxx"<<std::endl;
    }

}