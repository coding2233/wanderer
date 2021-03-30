#include "gateway/gateway_module.h"

namespace wanderer
{
    GatewayModule::GatewayModule(System *system) : Module(system)
    {
    }

    GatewayModule::~GatewayModule()
    {
    }

    //初始化函数
    void GatewayModule::OnInit()
    {
        GetSystem()->GetModule<NetworkModule>()->AddReciveListener(std::bind(&GatewayModule::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2));
    }

    //循环
    void GatewayModule::OnUpdate()
    {
    }

    //关闭
    void GatewayModule::OnClose()
    {
    }

    //处理消息
    void GatewayModule::OnMessageReceive(const Session *session, IMessage *message)
    {
        auto msg = dynamic_cast<Message *>(message);
        if (msg->message_type_ == MessageType_Inner)
        {
            auto app_config = GetSystem()->app_config_;
            //网关负责转发消息
            if (app_config->app_type_ == AppType_Gateway)
            {
                auto session = GetSystem()->GetModule<InnerSessionModule>()->GetGateSession((AppType_)msg->inner_receiver_);
                session->Send(message);
            }
        }
    }

} // namespace wanderer