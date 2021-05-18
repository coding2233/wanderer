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
        actor_address_center_index = (int)ActorAddress_CENTER_START_INDEX;
        thread_count_ = 16;
#if __unix__
        //Only Linux gets the number of CPUs
        thread_count_ = sysconf(_SC_NPROCESSORS_ONLN) * 2;
#endif
        LOG(INFO) << "[ActorModule] Number of threads: " << thread_count_;
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
            //找不到目标地址，就全由center转发
            if (GetSystem()->app_config_->app_type_ == AppType_Center)
            {
                auto forward_iter = sessions_.find(to_address);
                if (forward_iter != sessions_.end())
                {
                    forward_iter->second->Send(MessageType_Actor, data, size);
                }
                else
                {
                    LOG(ERROR) << "The center server does not have a corresponding forwarded Session: "
                               << " to_address: " << to_address << " from_address: " << from_address;
                }
            }
            else
            {
                LOG(ERROR) << " actors_ not find to_address !! from_address: " << from_address << " to_address: " << to_address;
            }
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

    void ActorModule::UpdateAddress(int old_address, int new_address, Actor *actor)
    {
        auto iter = actors_.find(old_address);
        if (iter != actors_.end())
        {
            actors_.erase(iter);
        }
        // iter = actors_.find(new_address);
        // if (iter != actors_.end()||)
        // {
        //     /* code */
        // }
        Register(actor, new_address);
        //更新地址对应的session
        auto session_iter = sessions_.find(old_address);
        if (session_iter != sessions_.end())
        {
            Session *session = session_iter->second;
            sessions_.erase(session_iter);
            sessions_[new_address] = session;
        }
    }

    int ActorModule::GetNewAddress()
    {
        return --actor_address_center_index;
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
            if (GetSystem()->app_config_->app_type_ != AppType_Center)
            {
                auto inner_session = GetSystem()->GetModule<NetworkModule>()->GetInnerSession();
                inner_session->Send(to_address, from_address, message_entilty_);
            }
            else
            {
                // GetSystem()->GetModule<CenterModule>()->
                LOG(ERROR) << "No Session corresponding to the address was found! [" << to_address << "]";
            }
        }
    }

}