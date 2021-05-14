#include "actor/actor_module.h"
#include "actor/actor.h"
#include "utility/utility.h"
#include <new>


namespace wanderer 
{
    // std::vector<Actor*> ActorModule::work_actors_;

    ActorModule::ActorModule(System *system) : Module(system)
    {
        thread_count_=16;
        #if __unix__
        //Only Linux gets the number of CPUs
        thread_count_=sysconf(_SC_NPROCESSORS_ONLN)*2;
        #endif
        thread_pool_=new ThreadPool(thread_count_);
    }

    ActorModule::~ActorModule()
    {
        delete thread_pool_;
    }

    //初始化函数
    void ActorModule::OnInit() 
    {
    }
    //循环
    void ActorModule::OnUpdate() 
    {
        if (work_actors_.size()==0) 
            return;
        for (auto iter=work_actors_.begin(); iter!=work_actors_.end(); iter++)
        {
            Actor* actor = (*iter);
            int state = actor->GetState();
            if (state == 1) 
            {
                thread_pool_->enqueue([](Actor* actor){actor->Handle();},actor);
            }
            else if (state==0) 
            {
                work_actors_.erase(iter);
                break;
            }
        }
    }

    //关闭
    void ActorModule::OnClose()
    {
    }

    void ActorModule::HandleMessage(Session *session,const char * data,size_t size)
    {
        int to_address = CharPointer2Int(data);
        int from_address = CharPointer2Int(data+4);

        // CheckActorMapSessions(to_address,from_address,session);

        jsonrpcpp::entity_ptr entity = jsonrpcpp::Parser::do_parse(std::string(data+8, size-8));
        auto actor_iter = actors_.find(to_address);
        if (actor_iter!=actors_.end()) 
        {
            actor_iter->second->ToMailBox(Mail(session,entity,from_address));
            //Add Actor to the Work array.
            bool has_same_actor=false;
            Actor* actor = actor_iter->second;
            for (auto iter=work_actors_.begin(); iter!=work_actors_.end(); iter++) 
            {
                if (actor==*iter) 
                {
                    has_same_actor=true;
                    break;
                }
            }
            if (!has_same_actor) 
            {
                work_actors_.push_back(actor);
            }
        }
    }
}