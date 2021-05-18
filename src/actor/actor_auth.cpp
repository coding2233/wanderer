#include "actor/actor_auth.h"

namespace wanderer
{

    ActorAuth::ActorAuth() : Actor()
    {
        LOG(DEBUG) << "ActorAuth::ActorAuth ";
    }

    ActorAuth::~ActorAuth()
    {
    }

    void ActorAuth::MailHandler(Mail mail)
    {
        LOG(DEBUG) << "ActorAuth::MailHandler(Mail mail): " << mail.from_address_;

        if (mail.message_->is_response())
        {
            jsonrpcpp::response_ptr response = std::dynamic_pointer_cast<jsonrpcpp::Response>(mail.message_);
            LOG(DEBUG) << "[[[[[[[[[[[[[[[[[" << response->to_json().dump() << "]]]]]]]]]]]]]]]]]]]]]";
        }
    }

}