#ifndef __INNER_SESSION_MODULE_H__
#define __INNER_SESSION_MODULE_H__

#include "base/module.h"
#include "network/session.h"

#include <map>

namespace wanderer
{
    class InnerSessionModule: public Module
    {
    public:
        InnerSessionModule(System *system);
        ~InnerSessionModule();
    private:
        std::map<std::string,const Session*> inner_sessions_;
        std::map<std::string,const Session*> inner_gate_sessions_;
    public:
        
        void OnInit() override;
        void OnUpdate() override;
        void OnClose() override;
    
        void AddInnerGateSession(std::string name,const Session* session);
        void AddInnerSession(std::string name,const Session* session);

       
    };
}

#endif

