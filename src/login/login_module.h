#ifndef __LOGIN_MODULE_H__
#define __LOGIN_MODULE_H__

#include <map>

#include "base/module.h"
#include "network/network_module.h"
#include "network/message.h"
#include "base/app_config.h"

namespace wanderer
{
    class LoginModule : public Module
    {
    private:
        /* data */
        // InnerSession *inner_session_;
        
        std::map<std::string, const Session*> login_sessions_;

        //处理消息
        void OnMessageReceive(const Session* session, IMessage* message);

    public:
        LoginModule(System *system);
        ~LoginModule();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;
    };
} // namespace wanderer
#endif