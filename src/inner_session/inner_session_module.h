#ifndef __INNER_SESSION_MODULE_H__
#define __INNER_SESSION_MODULE_H__

#include "base/app_config.h"
#include "base/module.h"
#include "network/session.h"

#include <map>

namespace wanderer
{
    class InnerSessionModule : public Module
    {
    public:
        InnerSessionModule(System *system);
        ~InnerSessionModule();

    private:
        //For the time being, only one server of all types is supported!!!

        //normal inner session
        std::map<const char, Session *> inner_sessions_;
        //gate server inner session
        std::map<const char, std::vector<Session *>> inner_center_sessions_;

        std::map<Session *, bool> inner_all_sessions_;

    public:
        void OnInit() override;
        void OnUpdate() override;
        void OnClose() override;

        void AddInnerCenterSession(const char name, Session *session);
        void AddInnerSession(const char name, Session *session);

        Session *GetCenterSession(AppType_ app_type);
        Session *GetNormalSession(AppType_ app_type);

        void InnerAuth(Session *session);

        bool IsInner(Session *session);
    };
}

#endif
