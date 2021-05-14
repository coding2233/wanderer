#include "actor/actor.h"

namespace wanderer
{
    Actor::Actor(int address)
    {
        processing_=false;
        address_=address;
    }

    Actor::~Actor()
    {

    }

    void Actor::ToMailBox(Mail mail)
    {
        mtx_.lock();
        mail_box_.push(mail);
        mtx_.unlock();
    }

    void Actor::MailHandler(Mail mail)
    {

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
            if (mail_box_.size()>0) 
            {
                return 1;
            }
            
        }
        return  0;
    }

    void Actor::Handle()
    {
        processing_=true;
        if (mail_box_.size()>0) 
        {
            mtx_.lock();
            Mail mail = mail_box_.front();
            mail_box_.pop();
            mtx_.unlock();
            //处理消息
            MailHandler(mail);
        }
        processing_=false;
    }
}