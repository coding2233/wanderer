#ifndef __LOGIN_MODULE_H__
#define __LOGIN_MODULE_H__

#include <map>

#include "base/app_config.h"
#include "base/module.h"
#include "network/message.h"
#include "network/network_module.h"

namespace wanderer
{
    class LoginModule : public Module
    {
    private:
        /* data */
        // InnerSession *inner_session_;

        std::map<std::string, const Session *> login_sessions_;

        //处理消息
        void OnMessageReceive(Session *session, MessageType_ message_type, const char *data, size_t size);

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