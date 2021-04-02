#include "center/center_module.h"

namespace wanderer
{
    CenterModule::CenterModule(System *system) : Module(system)
    {
    }

    CenterModule::~CenterModule()
    {
    }

    //初始化函数
    void CenterModule::OnInit()
    {
        // GetSystem()->GetModule<NetworkModule>()->AddReciveListener(std::bind(&CenterModule::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2));
    }

    //循环
    void CenterModule::OnUpdate()
    {
    }

    //关闭
    void CenterModule::OnClose()
    {
    }

    //处理消息
    void CenterModule::OnMessageReceive(const Session *session, IMessage *message)
    {
        // auto msg = dynamic_cast<Message *>(message);
        // if (msg->message_type_ == MessageType_Inner)
        // {
        //     auto app_config = GetSystem()->app_config_;
        //     //网关负责转发消息
        //     if (app_config->app_type_ == AppType_Center)
        //     {
        //         auto session = GetSystem()->GetModule<InnerSessionModule>()->GetGateSession((AppType_)msg->inner_receiver_);
        //         session->Send(message);
        //     }
        // }
    }

} // namespace wanderer