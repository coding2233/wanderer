#ifndef __C2G_REGISTER_INNER_SESSION_H__
#define __C2G_REGISTER_INNER_SESSION_H__

#include "network/message_hander.h"
#include "wanderer.pb.h"
#include "network/session.h"

#include <iostream>

namespace wanderer
{
class S2G_RegisterInnerSessionHandler : public MessageHandler<S2G_RegisterInnerSession>
{
private:
    /* data */
public:
    S2G_RegisterInnerSessionHandler(/* args */);
    ~S2G_RegisterInnerSessionHandler();

    void Handle(const Session *session, S2G_RegisterInnerSession *message) override;
};
} // namespace wanderer

#endif