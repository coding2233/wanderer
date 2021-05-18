#include "actor/actor_inner.h"
#include "actor/actor.h"

namespace wanderer
{

    ActorInner::ActorInner() : Actor()
    {
        LOG(DEBUG) << "ActorInner::ActorInner ";
    }

    ActorInner::~ActorInner()
    {
    }

    void ActorInner::MailHandler(Mail mail)
    {
        LOG(DEBUG) << "ActorInner::MailHandler(Mail mail): " << mail.from_address_;

        if (mail.message_->is_response())
        {
            jsonrpcpp::response_ptr response = std::dynamic_pointer_cast<jsonrpcpp::Response>(mail.message_);
            LOG(DEBUG) << "[[[[[[[[[[[[[[[[[" << response->to_json().dump() << "]]]]]]]]]]]]]]]]]]]]]";
        }
    }

}