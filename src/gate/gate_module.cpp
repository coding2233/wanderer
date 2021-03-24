#include "gate/gate_module.h"

namespace wanderer
{
    GateModule::GateModule(System *system) : Module(system)
    {
    }

    GateModule::~GateModule()
    {
    }

    //初始化函数
    void GateModule::OnInit()
    {
        GetSystem()->GetModule<NetworkModule>()->AddReciveListener(std::bind(&GateModule::OnMessageReceive, this, std::placeholders::_1, std::placeholders::_2));
    }

    //循环
    void GateModule::OnUpdate()
    {
    }

    //关闭
    void GateModule::OnClose()
    {
    }

    //处理消息
    void GateModule::OnMessageReceive(const Session* session, IMessage* message)
    {
        auto msg = dynamic_cast<Message*>(message);
        if (msg->message_type_ == MessageType_Inner)
        {
            auto app_config = GetSystem()->app_config_;
            //网关负责转发消息
            if (app_config->app_type_ == AppType_Gate)
            {
                auto session =GetSystem()->GetModule<InnerSessionModule>()->GetGateSession((AppType_)msg->inner_receiver_);
                session->Send(message);
            }

        }

    }

} // namespace wanderer