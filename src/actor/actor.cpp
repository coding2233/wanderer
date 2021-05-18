#include "actor/actor.h"

namespace wanderer
{

    Actor::Actor()
    {
        processing_ = false;
    }

    Actor::~Actor()
    {
    }

    void Actor::ToMailBox(Mail mail)
    {
        LOG(INFO) << "Actor::ToMailBox(Mail mail)  [mtx_.lock()]";
        mtx_.lock();
        mail_box_.push(mail);
        LOG(INFO) << "Actor::ToMailBox(Mail mail) mail_box_.size(): " << mail_box_.size();
        mtx_.unlock();
        LOG(INFO) << "Actor::ToMailBox(Mail mail)  [mtx_.unlock()]";
    }

    void Actor::MailHandler(Mail mail)
    {
    }

    void Actor::Setup(const int address, SEND_MAIL send_mail)
    {
        address_ = address;
        send_mail_ = send_mail;
    }

    int Actor::GetAddress()
    {
        return address_;
    }

    int Actor::GetState()
    {
        if (processing_)
        {
            return 2;
        }
        else
        {
            if (mail_box_.size() > 0)
            {
                return 1;
            }
        }
        return 0;
    }

    void Actor::Handle()
    {
        if (processing_)
            return;

        processing_ = true;
        LOG(DEBUG) << "Actor::Handle() mail_box_.size(): " << mail_box_.size();
        if (mail_box_.size() > 0)
        {
            LOG(INFO) << "Actor::Handle()  [mtx_.lock()]";
            mtx_.lock();
            Mail mail = mail_box_.front();
            mail_box_.pop();
            mtx_.unlock();
            LOG(INFO) << "Actor::Handle()  [mtx_.unlock()]";
            //处理消息
            MailHandler(mail);
        }
        processing_ = false;
    }
}