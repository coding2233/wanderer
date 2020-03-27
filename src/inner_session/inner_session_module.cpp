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

    void InnerSessionModule::AddInnerGateSession(std::string name,const Session* session)
    {
        auto iter=inner_gate_sessions_.find(name);
        if(iter==inner_gate_sessions_.end())
        {
            inner_gate_sessions_.insert(std::make_pair(name,session));
        }
    }

    void InnerSessionModule::AddInnerSession(std::string name,const Session* session)
    {
        auto iter= inner_sessions_.find(name);
        if(iter==inner_sessions_.end())
        {
            inner_sessions_.insert(std::make_pair(name,session));
        }
    }
}
