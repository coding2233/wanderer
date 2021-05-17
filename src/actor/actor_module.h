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
#include "network/session.h"
#include "utility/thread_pool.h"
#include "utility/utility.h"

namespace wanderer
{
    enum ActorAddress_ : int
    {
        ActorAddress_LOGIN = -1,
        ActorAddress_CENTER = -2,
        ActorAddress_DATABASE = -3,
        ActorAddress_GATEWAY = -4,
        ActorAddress_CENTER_AUTH = -5
    };

    class ActorModule : public Module
    {
    private:
        int thread_count_;
        ThreadPool *thread_pool_;

        std::map<const int, Actor *> actors_;
        static int actor_address_index;

        std::vector<Actor *> work_actors_;

    public:
        ActorModule(System *system);
        ~ActorModule();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;

        void Register(Actor *actor, int address = 0);

        void HandleMessage(Session *session, const char *data, size_t size);
    };
}
#endif