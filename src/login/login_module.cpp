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
        YAML::Node node = YAML::Load(std::string(data, size));
        if (GetSystem()->GetModule<InnerSessionModule>()->IsInner(session))
        {
        }
        else
        {
        }

        // auto msg = dynamic_cast<Message *>(message);
        // if (msg->message_code_ == MessageCode_Login_C2S)
        // {
        //     auto app_type = GetSystem()->app_config_->app_type_;
        //     auto inner_session = GetSystem()->GetModule<InnerSessionModule>()->GetNormalSession(app_type);
        //     msg->message_type_ = MessageType_Inner;
        //     msg->inner_sender_ = (char)app_type;
        //     msg->inner_receiver_ = AppType_DataBase;
        //     inner_session->Send(msg);

        //     //login_sessions_.insert(std::pair<std::string,const Session*>("", session));
        // }
        // else if (msg->message_code_ == MessageCode_Login_S2C)
        // {
        //     // Sends the login failure result to the client.
        // }
    }

} // namespace wanderer