#include "login/login_module.h"
#include "network/message.h"
#include "utility/jsonrpcpp.hpp"
#include <string>

namespace wanderer
{
    LoginModule::LoginModule(System *system) : Module(system)
    {
    }

    LoginModule::~LoginModule()
    {
    }

    //初始化函数
    void LoginModule::OnInit()
    {
        auto app_config = GetSystem()->app_config_;

        GetSystem()->GetModule<NetworkModule>()->AddInnerReceiveListener(MessageType_2L,std::bind(&LoginModule::OnInnerMessageReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
        GetSystem()->GetModule<NetworkModule>()->AddReciveListener(std::bind(&LoginModule::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

        GetSystem()->GetModule<NetworkModule>()->CreateInnerSession(AppType_Login, app_config->center_ip_.c_str(), app_config->center_port_);
    }

    //循环
    void LoginModule::OnUpdate()
    {
        //inner_session_->Loop();
    }

    //关闭
    void LoginModule::OnClose()
    {
        //  delete inner_session_;
    }

    void LoginModule::OnInnerMessageReceive(Session* session, MessageType_ message_type, jsonrpcpp::entity_ptr entity)
    {

    }

    void LoginModule::OnMessageReceive(Session *session, MessageType_ message_type, const char *data, size_t size)
    {
        if (message_type != MessageType_2L) 
        {
            return;
        }

        LOG(INFO)<<"LoginModule::OnMessageReceive message: "<<std::string(data, size);

        jsonrpcpp::entity_ptr entity = jsonrpcpp::Parser::do_parse(std::string(data, size));
        if (entity) 
        {
            if (entity->is_request()) 
            {
                jsonrpcpp::request_ptr request = std::dynamic_pointer_cast<jsonrpcpp::Request>(entity);
                if(request->method()=="login")
                {
                    // jsonrpcpp::Response(*request, result);
                    auto user_name = request->params().get<std::string>(0);
                    LOG(INFO)<<"LOGIN MODULE: "<<request->to_json().dump();
                    auto respone= jsonrpcpp::Response(*request,Json({true,"登陆成功！！！dsfsd#"}));
                   
                    auto data= respone.to_json().dump();
                    std::string message_data(data.c_str(),data.size());
                    Message message;
                    message.Setup(MessageType_2L,message_data.c_str(),message_data.size());
                    session->Send(&message);
                    // auto user_name = request->params().get<std::string>("user_name")
                }
            }
        }
      
    }

} // namespace wanderer