#ifndef __TEST_MESSAGE_HANDLE_H__
#define __TEST_MESSAGE_HANDLE_H__

#include "network/message_hander.h"
#include "test.pb.h"
#include "network/session.h"

#include <iostream>

namespace wanderer
{
class TestMessageHandler : public MessageHandler<TestMessage>
{
private:
    /* data */
public:
    TestMessageHandler();
    ~TestMessageHandler();

protected:
    void Handle(const Session *session, TestMessage *message) override;
};
} // namespace wanderer

#endif