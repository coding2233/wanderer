#ifndef __ACTOR_H__
#define __ACTOR_H__

#include <functional>
#include <mutex>
#include <queue>

#include "base/easylogging++.h"
#include "base/system.h"
#include "utility/jsonrpcpp.hpp"

namespace wanderer
{

#define SEND_MAIL std::function<void(int, int, jsonrpcpp::entity_ptr)>

    struct Mail
    {
        int to_address_;
        jsonrpcpp::entity_ptr message_;
        int from_address_;

        Mail(int to_address, int from_address, jsonrpcpp::entity_ptr message)
        {
            to_address_ = to_address;
            from_address_ = from_address;
            message_ = message;
        }
    };

    enum ActorAddress_ : int
    {
        ActorAddress_START_INDEX = 0,
        ActorAddress_ALL = -1,
        ActorAddress_LOGIN = -2,
        ActorAddress_CENTER = -3,
        ActorAddress_DATABASE = -4,
        ActorAddress_GATEWAY = -5,
        ActorAddress_CENTER_START_INDEX = -100,
    };

    class Actor
    {
    private:
        int address_;
        std::queue<Mail> mail_box_;
        std::mutex mtx_;
        bool processing_;

    protected:
        virtual void OnMailHandle(Mail mail);

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
