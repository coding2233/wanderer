#include "center/actor_center.h"

namespace wanderer
{
    ActorCenter::ActorCenter() : Actor()
    {
    }

    ActorCenter::~ActorCenter()
    {
    }

    void ActorCenter::MailHandler(Mail mail)
    {
        LOG(DEBUG) << "ActorCenter::MailHandler(Mail mail): " << mail.from_address_;

        if (mail.message_->is_request())
        {
            jsonrpcpp::request_ptr request = std::dynamic_pointer_cast<jsonrpcpp::Request>(mail.message_);
            if (request->method() == "auth")
            {
                AppType_ app_type = (AppType_)request->params().get<int>(0);
                std::string secret_key = request->params().get<std::string>(1);
                LOG(DEBUG) << "ActorCenter [auth] verification information: " << app_type << " " << secret_key;

                jsonrpcpp::response_ptr respone = std::make_shared<jsonrpcpp::Response>(*request, Json({true, "Internal server validation successful."}));
                send_mail_(mail.from_address_, GetAddress(), respone);
            }
        }
    }

}