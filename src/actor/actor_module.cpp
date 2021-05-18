#include "actor/actor_module.h"
#include "actor/actor.h"
#include "utility/utility.h"
#include <new>

namespace wanderer
{
    // std::vector<Actor*> ActorModule::work_actors_;

    ActorModule::ActorModule(System *system) : Module(system)
    {
        actor_address_index = 0;
        thread_count_ = 16;
#if __unix__
        //Only Linux gets the number of CPUs
        thread_count_ = sysconf(_SC_NPROCESSORS_ONLN) * 2;
#endif
        thread_pool_ = new ThreadPool(thread_count_);

        send_mail_ = std::bind(&ActorModule::SendMail, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
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
        if (work_actors_.size() == 0)
            return;
        // LOG(INFO) << "[00] ActorModule::OnUpdate() work_actors_.size(): " << work_actors_.size();

        for (auto iter = work_actors_.begin(); iter != work_actors_.end(); iter++)
        {
            Actor *actor = (*iter);
            int state = actor->GetState();
            if (state == 1)
            {
                thread_pool_->enqueue([](Actor *actor)
                                      { actor->Handle(); },
                                      actor);
            }
            else if (state == 0)
            {
                work_actors_.erase(iter);
                // work_actors_.erase(iter++);
                break;
            }
        }
    }

    //关闭
    void ActorModule::OnClose()
    {
    }

    void ActorModule::HandleMessage(Session *session, const char *data, size_t size)
    {
        int to_address = CharPointer2Int(data);
        int from_address = CharPointer2Int(data + 4);

        sessions_[from_address] = session;

        LOG(INFO) << "ActorModule::HandleMessage to_address: " << to_address << " from_address: " << from_address << " actors_.size(): " << actors_.size();
        auto actor_iter = actors_.find(to_address);
        if (actor_iter != actors_.end())
        {
            LOG(DEBUG) << "actors_ find to_address !!";

            jsonrpcpp::entity_ptr entity = jsonrpcpp::Parser::do_parse(std::string(data + 8, size - 8));
            actor_iter->second->ToMailBox(Mail(session, entity, from_address));
            //Add Actor to the Work array.
            bool has_same_actor = false;
            Actor *actor = actor_iter->second;
            for (auto iter = work_actors_.begin(); iter != work_actors_.end(); iter++)
            {
                if (actor == *iter)
                {
                    LOG(INFO) << "Receive multiple Mails. " << to_address;
                    has_same_actor = true;
                    break;
                }
            }
            if (!has_same_actor)
            {
                LOG(INFO) << "Get ready for email. " << to_address << " work_actors_.size(): " << work_actors_.size();
                work_actors_.push_back(actor);
            }
        }
        else
        {
            LOG(DEBUG) << " [*****] actors_ not find to_address !!";
            //找不到目标地址，就全由center转发
            //
        }
    }

    void ActorModule::Register(Actor *actor, int address)
    {
        if (address == 0)
        {
            address = ++actor_address_index;
        }
        actor->Setup(address, send_mail_);
        actors_[address] = actor;
    }

    void ActorModule::SendMail(int to_address, int from_address, jsonrpcpp::entity_ptr message_entilty_)
    {
        auto iter = sessions_.find(to_address);
        if (iter != sessions_.end())
        {
            iter->second->Send(to_address, from_address, message_entilty_);
        }
        else
        {
            LOG(ERROR) << "No Session corresponding to the address was found! [" << to_address << "]";
        }
    }

}