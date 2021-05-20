#include "login/login_module.h"

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
        // GetSystem()->GetModule<ActorModule>()->Register(new ActorLogin, ActorAddress_LOGIN);
    }

    //循环
    void LoginModule::OnUpdate()
    {
    }

    //关闭
    void LoginModule::OnClose()
    {
    }

    // void LoginModule::OnMessageReceive(Session *session, MessageType_ message_type, const char *data, size_t size)
    // {
    //     if (message_type != MessageType_2L)
    //     {
    //         return;
    //     }

    //     LOG(INFO)<<"LoginModule::OnMessageReceive message: "<<std::string(data, size);

    //     jsonrpcpp::entity_ptr entity = jsonrpcpp::Parser::do_parse(std::string(data, size));
    //     if (entity)
    //     {
    //         if (entity->is_request())
    //         {
    //             jsonrpcpp::request_ptr request = std::dynamic_pointer_cast<jsonrpcpp::Request>(entity);
    //             if(request->method()=="login")
    //             {
    //                 // jsonrpcpp::Response(*request, result);
    //                 auto user_name = request->params().get<std::string>(0);
    //                 LOG(INFO)<<"LOGIN MODULE: "<<request->to_json().dump();
    //                 auto respone= jsonrpcpp::Response(*request,Json({true,"登陆成功！！！dsfsd#"}));

    //                 auto data= respone.to_json().dump();
    //                 std::string message_data(data.c_str(),data.size());
    //                 Message message;
    //                 message.Setup(MessageType_2L,message_data.c_str(),message_data.size());
    //                 session->Send(&message);
    //                 // auto user_name = request->params().get<std::string>("user_name")
    //             }
    //         }
    //     }

    // }

} // namespace wanderer