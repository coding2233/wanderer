#include "actor_database.h"

namespace wanderer
{
    ActorDatabase::ActorDatabase(/* args */)
    {
    }

    ActorDatabase::~ActorDatabase()
    {
    }

    void ActorDatabase::MailHandler(Mail mail)
    {
        LOG(DEBUG) << mail.message_->to_json().dump();
        if (mail.message_->is_request())
        {
            jsonrpcpp::request_ptr request = std::dynamic_pointer_cast<jsonrpcpp::Request>(mail.message_);
            if (request->method() == "login")
            {
                auto user_name = request->params().get<std::string>("username");
                auto password = request->params().get<std::string>("password");
                //验证密码是否正确
                auto response = std::make_shared<jsonrpcpp::Response>(*request, Json({{"success", true}, {"username", user_name}}));
                LOG(DEBUG) << response->to_json().dump();
                send_mail_(mail.from_address_, GetAddress(), response);
            }
        }
    }
}