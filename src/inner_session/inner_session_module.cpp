#include "inner_session/inner_session_module.h"

namespace wanderer
{
    InnerSessionModule::InnerSessionModule(System *system) : Module(system)
    {
    }

    InnerSessionModule::~InnerSessionModule()
    {
    }

    void InnerSessionModule::OnInit()
    {
    }

    void InnerSessionModule::OnUpdate()
    {
    }

    void InnerSessionModule::OnClose()
    {
    }

    void InnerSessionModule::AddInnerCenterSession(const char name, Session *session)
    {
        //需要判断有是否认证过的session
        auto iter = inner_center_sessions_.find(name);
        std::vector<Session *> *sessions = nullptr;
        if (iter == inner_center_sessions_.end())
        {
            std::vector<Session *> new_sessions;
            sessions = &new_sessions;
            inner_center_sessions_.insert(std::make_pair(name, new_sessions));
        }
        else
        {
            sessions = &iter->second;
        }
        // for (size_t i = 0; i < sessions->size(); i++)
        // {
        //     if (sessions[i].fd_ == session.fd_)
        //         return;
        // }
        sessions->push_back(session);
        //添加到所有的内部会话中
        inner_all_sessions_.insert(std::make_pair(session, true));
    }

    void InnerSessionModule::AddInnerSession(const char name, Session *session)
    {
        auto iter = inner_sessions_.find(name);
        if (iter == inner_sessions_.end())
        {
            inner_sessions_.insert(std::make_pair(name, session));
            //添加到所有的内部会话中
            inner_all_sessions_.insert(std::make_pair(session, true));
        }
    }

    Session *InnerSessionModule::GetCenterSession(AppType_ app_type)
    {
        auto iter = inner_center_sessions_.find(app_type);
        if (iter != inner_center_sessions_.end())
        {
            //判断优先级
            //暂没做逻辑处理，默认第一个
            auto session = iter->second[0];
            return session;
        }
        return nullptr;
    }

    Session *InnerSessionModule::GetNormalSession(AppType_ app_type)
    {
        auto iter = inner_sessions_.find(app_type);
        if (iter != inner_sessions_.end())
        {
            return iter->second;
        }
        return nullptr;
    }

    void InnerSessionModule::InnerAuth(Session *session)
    {
        for (auto iter = inner_sessions_.begin(); iter != inner_sessions_.end(); iter++)
        {
            if (iter->second == session)
            {
                session->InnerAuth((AppType_)iter->first);
                break;
            }
            // iter->second->InnerAuth((AppType_)iter->first);
        }
    }

    bool InnerSessionModule::IsInner(Session *session)
    {
        auto iter = inner_all_sessions_.find(session);
        return iter != inner_all_sessions_.end();
    }

}
