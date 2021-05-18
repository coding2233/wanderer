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
                LOG(DEBUG) << "ActorCenter [auth] verification information: " << std::to_string(app_type) << " " << secret_key;
                bool result = System::app_config_->secret_key_ == secret_key;
                //int new_address = 0;
                // if (result)
                // {
                //     if (app_type == AppType_All)
                //     {
                //         new_address = ActorAddress_ALL;
                //     }
                //     else if (app_type == AppType_Login)
                //     {
                //         new_address = ActorAddress_LOGIN;
                //     }
                //     else if (app_type == AppType_DataBase)
                //     {
                //         new_address = ActorAddress_DATABASE;
                //     }
                //     else
                //     {
                //         new_address = System::GetModule<ActorModule>()->GetNewAddress();
                //     }
                //     System::GetModule<CenterModule>()->AppAuth(app_type, new_address);
                // }
                System::GetModule<CenterModule>()->AppAuth(app_type, mail.from_address_);
                jsonrpcpp::response_ptr respone = std::make_shared<jsonrpcpp::Response>(*request, Json({result, mail.from_address_}));
                send_mail_(mail.from_address_, GetAddress(), respone);
            }
        }
    }

}