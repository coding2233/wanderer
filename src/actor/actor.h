#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <queue>
#include <mutex>
#if __unix
#include <bits/stdint-intn.h>
#endif

#include "network/session.h"
#include "utility/jsonrpcpp.hpp"


namespace wanderer 
{
    struct Mail
    {
        Session* session_;
        jsonrpcpp::entity_ptr message_entilty_;
        int from_address_;

        Mail(Session* session,jsonrpcpp::entity_ptr message_entilty, int from_address)
        {
            session_=session;
            message_entilty_=message_entilty;
            from_address_=from_address;
        }
    };

    class Actor
    {
    private:
        int address_;
        std::queue<Mail> mail_box_;
        std::mutex mtx_;
        bool processing_;
    protected:
        virtual void MailHandler(Mail mail);
    public:
        Actor(int address);
        virtual ~Actor();

        int GetAddress();

        int GetState();

        void ToMailBox(Mail mail);


        void Handle();
    };
}

//state 
//behaviour
//emailbox

#endif
