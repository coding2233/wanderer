#include "inner_session/inner_session_module.h"

namespace wanderer
{
    InnerSessionModule::InnerSessionModule(System *system):Module(system)
    {}

    InnerSessionModule::~InnerSessionModule()
    {}

    void InnerSessionModule::OnInit()
    {}

    void InnerSessionModule::OnUpdate()
    {}

    void InnerSessionModule::OnClose()
    {}

    void InnerSessionModule::AddInnerGateSession(char name,Session* session)
    {
        auto iter=inner_gate_sessions_.find(name);
        if(iter==inner_gate_sessions_.end())
        {
            inner_gate_sessions_.insert(std::make_pair(name,session));
        }
    }

    void InnerSessionModule::AddInnerSession(char name,Session* session)
    {
        auto iter= inner_sessions_.find(name);
        if(iter==inner_sessions_.end())
        {
            inner_sessions_.insert(std::make_pair(name,session));
        }
    }

    Session* InnerSessionModule::GetGateSession(AppType_ app_type)
    {
        auto iter = inner_gate_sessions_.find(app_type);
        if (iter!= inner_gate_sessions_.end())
        {
            return iter->second;
        }

        return nullptr;
    }

    Session* InnerSessionModule::GetNormalSession(AppType_ app_type)
    {
        auto iter = inner_sessions_.find(app_type);
        if (iter != inner_sessions_.end())
        {
            return iter->second;
        }

        return nullptr;
    }

}
