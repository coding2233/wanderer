#ifndef __INNER_SESSION_MODULE_H__
#define __INNER_SESSION_MODULE_H__

#include "base/module.h"
#include "network/session.h"
#include "base/app_config.h"

#include <map>

namespace wanderer
{
    class InnerSessionModule: public Module
    {
    public:
        InnerSessionModule(System *system);
        ~InnerSessionModule();
    private:
        //For the time being, only one server of all types is supported!!!

        //normal inner session
        std::map<char,Session*> inner_sessions_;
        //gate server inner session
        std::map<char,Session*> inner_gate_sessions_;
    public:
        
        void OnInit() override;
        void OnUpdate() override;
        void OnClose() override;
    
        void AddInnerGateSession(char name,Session* session);
        void AddInnerSession(char name,Session* session);

        Session* GetGateSession(AppType_ app_type);
        Session* GetNormalSession(AppType_ app_type);
    };
}

#endif

