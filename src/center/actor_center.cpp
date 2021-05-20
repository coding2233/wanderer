#include "center/actor_center.h"

namespace wanderer
{
    ActorCenter::ActorCenter() : Actor()
    {
    }

    ActorCenter::~ActorCenter()
    {
    }

    void ActorCenter::OnMailHandle(Mail mail)
    {
        LOG(DEBUG) << "ActorCenter::OnMailHandle(Mail mail): " << mail.from_address_;

        if (mail.message_->is_request())
        {
            jsonrpcpp::request_ptr request = std::dynamic_pointer_cast<jsonrpcpp::Request>(mail.message_);
            if (request->method() == "auth")
            {
                AppType_ app_type = (AppType_)request->params().get<int>("apptype");
                std::string secret_key = request->params().get<std::string>("secretkey");
                LOG(DEBUG) << "ActorCenter [auth] verification information: " << std::to_string(app_type) << " " << secret_key;
                bool result = System::app_config_->secret_key_ == secret_key;
                if (result)
                {
                    System::GetModule<CenterModule>()->AppAuth(app_type, mail.from_address_);
                }
                jsonrpcpp::response_ptr respone = std::make_shared<jsonrpcpp::Response>(*request, Json(result));
                send_mail_(mail.from_address_, GetAddress(), respone);
            }
        }
    }

}