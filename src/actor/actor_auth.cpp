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
        LOG(DEBUG) << "from address: " << mail.from_address_ << " message: " << mail.message_->to_json().dump();

        if (mail.message_->is_response())
        {
            jsonrpcpp::response_ptr response = std::dynamic_pointer_cast<jsonrpcpp::Response>(mail.message_);
            Json result = response->to_json();
            bool success = result["result"].get<bool>();
            System::GetModule<NetworkModule>()->InnerSessionAuth(success);
            if (success)
            {
                LOG(INFO) << "Authentication is successful . ";
            }
        }
    }

}