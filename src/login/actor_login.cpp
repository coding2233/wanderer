#include "actor_login.h"

namespace wanderer
{
    ActorLogin::ActorLogin(/* args */) : Actor()
    {
    }

    ActorLogin::~ActorLogin()
    {
    }

    void ActorLogin::OnMailHandle(Mail mail)
    {
        LOG(DEBUG) << mail.message_->to_json().dump();
        if (mail.message_->is_request())
        {
            jsonrpcpp::request_ptr request = std::dynamic_pointer_cast<jsonrpcpp::Request>(mail.message_);
            if (request->method() == "login")
            {
                auto user_name = request->params().get<std::string>("username");
                // auto password = request->params().get<std::string>("password");
                login_response[user_name] = mail.from_address_;
                send_mail_(ActorAddress_DATABASE, GetAddress(), request);
            }
        }
        else if (mail.message_->is_response())
        {
            jsonrpcpp::response_ptr response = std::dynamic_pointer_cast<jsonrpcpp::Response>(mail.message_);
            Json result = response->result();
            std::string user_name = result["username"];
            for (auto iter = login_response.begin(); iter != login_response.end(); iter++)
            {
                if (iter->first == user_name)
                {
                    send_mail_(iter->second, GetAddress(), response);
                    login_response.erase(iter);
                    break;
                }
            }
        }
    }

}