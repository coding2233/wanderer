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

    //void InnerSessionModule::Send(std::string name,std::string target_name)
    //{
    //    auto iter = inner_sessions_.find(name);
    //    if (iter != inner_sessions_.end())
    //    {
    //        auto session = iter->second;
    //        //session->Send(Message::Global.Setup(MessageType_Inner,""))
    //        //session->Send(Message::Global.Setup(0,));
    //       /* Message* msg = new Message();
    //        session->Send(msg->Setup(0, 1, 2, "sdsdfsdf"));*/
    //        //iter->second->Send
    //    }
    //}

}
