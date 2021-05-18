#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <functional>
#include <mutex>
#include <queue>

#include "base/system.h"
#include "network/session.h"
#include "utility/jsonrpcpp.hpp"

namespace wanderer
{

#define SEND_MAIL std::function<void(int, int, jsonrpcpp::entity_ptr)>

    struct Mail
    {
        Session *session_;
        jsonrpcpp::entity_ptr message_;
        int from_address_;

        Mail(Session *session, jsonrpcpp::entity_ptr message, int from_address)
        {
            session_ = session;
            message_ = message;
            from_address_ = from_address;
        }
    };

    enum ActorAddress_ : int
    {
        ActorAddress_LOGIN = -1,
        ActorAddress_CENTER = -2,
        ActorAddress_DATABASE = -3,
        ActorAddress_GATEWAY = -4,
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

        SEND_MAIL send_mail_;

    public:
        Actor();
        virtual ~Actor();

        void Setup(const int address, SEND_MAIL send_mail);

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
