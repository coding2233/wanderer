#ifndef __ACTOR_MODEUL_H__
#define __ACTOR_MODEUL_H__

#include "utility/jsonrpcpp.hpp"
#include <map>
#include <utility>
#include <vector>
#if __unix__
#include <unistd.h>
#endif

#include "actor/actor.h"
#include "base/module.h"
#include "utility/thread_pool.h"
#include "utility/utility.h"
#include "network/session.h"

namespace wanderer 
{
    enum ActorAddress_:int
    {
        ActorAddress_LOGIN=-1,
        ActorAddress_CENTER=-2,
        ActorAddress_DATABASE=-3,
        ActorAddress_GATEWAY=-4,
        ActorAddress_CENTER_AUTH = -5 
    };

    class ActorModule:public Module
    {
    private:
        int thread_count_;
        ThreadPool *thread_pool_;

        std::map<int, Actor*> actors_;
        int actor_address_index;

        std::vector<Actor*> work_actors_;
public:
        ActorModule(System *system);
        ~ActorModule();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;

        template<class T>
        Actor *SpawnActor(int address=0)
        {
            if (address ==0) 
            {
                address=++actor_address_index;
            }
            Actor *actor= dynamic_cast< Actor *>(new T(address));
            actors_.insert(std::pair<int, Actor*>(address, actor));
            return actor;
        }

        void HandleMessage(Session *session,const char * data,size_t size);
        
    };
}
#endif