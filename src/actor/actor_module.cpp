#include "actor/actor_module.h"
#include "actor/actor.h"
#include "utility/utility.h"
#include <new>

namespace wanderer
{
    // std::vector<Actor*> ActorModule::work_actors_;

    ActorModule::ActorModule(System *system) : Module(system)
    {
        // actor_address_index = 0;
        // actor_address_center_index = (int)ActorAddress_CENTER_START_INDEX;
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
        if (mail_box_.size() > 0)
        {
            mail_box_mtx_.lock();
            Mail mail = mail_box_.front();
            mail_box_.pop();
            mail_box_mtx_.unlock();

            thread_pool_->enqueue([](Mail mail, ActorModule *am)
                                  { am->HandleMail(mail); },
                                  mail, this);
        }

        if (work_actors_.size() > 0)
        {
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
                    break;
                }
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

        if (session != nullptr)
        {
            sessions_[from_address] = session;
        }
        jsonrpcpp::entity_ptr entity = jsonrpcpp::Parser::do_parse(std::string(data + 8, size - 8));

        HandleMail(Mail(to_address, from_address, entity));
    }

    void ActorModule::HandleMail(Mail mail)
    {
        //接收邮件和发送邮件都从这里处理，可能有部分冗余的代码和计算

        int to_address = mail.to_address_;
        auto actor_iter = actors_.find(to_address);
        if (actor_iter != actors_.end())
        {
            LOG(DEBUG) << "actors_ find to_address !! " << to_address;
            actor_iter->second->ToMailBox(mail);
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
            auto session_iter = sessions_.find(to_address);
            if (session_iter != sessions_.end())
            {
                session_iter->second->Send(to_address, mail.from_address_, mail.message_);
            }
            else
            {
                //找不到目标地址，就全由center转发
                if (GetSystem()->app_config_->app_type_ == AppType_Center)
                {
                    int forward_address = GetSystem()->GetModule<CenterModule>()->ForwardAddress(to_address);
                    auto forward_iter = sessions_.find(forward_address);
                    if (forward_iter != sessions_.end())
                    {
                        std::string json_data = mail.message_->to_json().dump();
                        forward_iter->second->Send(MessageType_Actor, json_data.c_str(), json_data.size());
                    }
                    else
                    {
                        LOG(ERROR) << "The center server does not have a corresponding forwarded Session: "
                                   << " to_address: " << to_address << " from_address: " << mail.from_address_;
                    }
                }
                else if (GetSystem()->app_config_->app_type_ != AppType_All)
                {
                    auto inner_session = GetSystem()->GetModule<NetworkModule>()->GetInnerSession();
                    inner_session->Send(to_address, mail.from_address_, mail.message_);
                }
                else
                {
                    LOG(ERROR) << " actors_ not find to_address !! from_address: " << mail.from_address_ << " to_address: " << to_address;
                }
            }
        }
    }

    void ActorModule::Register(Actor *actor, int address)
    {
        if (address == 0)
        {
            address = GetNewAddress();
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
        bool update = true;
        int new_address = 0;
        int update_index = 0;
        do
        {
            new_address = rand();
            auto iter_actor = actors_.find(new_address);
            auto iter_session = sessions_.find(new_address);
            if (new_address > 0 && iter_actor == actors_.end() && iter_session == sessions_.end())
            {
                update = false;
            }
            if (++update_index >= 10)
            {
                LOG(WARNING) << "ActorModule fetches a new address more than 10 times at random to confirm whether there is too much data. " << update_index;
            }

        } while (update);

        return new_address;
    }

    void ActorModule::SendMail(int to_address, int from_address, jsonrpcpp::entity_ptr message)
    {
        mail_box_mtx_.lock();
        mail_box_.push(Mail(to_address, from_address, message));
        mail_box_mtx_.unlock();
    }

}