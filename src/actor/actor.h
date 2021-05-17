#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <mutex>
#include <queue>

#include "base/system.h"
#include "network/session.h"
#include "utility/jsonrpcpp.hpp"

namespace wanderer
{
    struct Mail
    {
        Session *session_;
        jsonrpcpp::entity_ptr message_entilty_;
        int from_address_;

        Mail(Session *session, jsonrpcpp::entity_ptr message_entilty, int from_address)
        {
            session_ = session;
            message_entilty_ = message_entilty;
            from_address_ = from_address;
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
        Actor();
        virtual ~Actor();

        void SetAddress(const int address);

        int GetAddress();

        int GetState();

        void ToMailBox(Mail mail);

        void SendMail(int to_address, jsonrpcpp::entity_ptr message_entilty_);

        void Handle();
    };
}

//state
//behaviour
//emailbox

#endif
