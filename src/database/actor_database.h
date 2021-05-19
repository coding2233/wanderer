#ifndef __ACTOR_DATABASE_H__
#define __ACTOR_DATABASE_H__

#include "actor/actor.h"

namespace wanderer
{
    class ActorDatabase : public Actor
    {
    private:
        /* data */
    protected:
        void MailHandler(Mail mail) override;

    public:
        ActorDatabase(/* args */);
        ~ActorDatabase();
    };

}

#endif