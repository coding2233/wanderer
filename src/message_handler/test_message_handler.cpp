
#include "message_handler/test_message_handler.h"

namespace wanderer
{
TestMessageHandler::TestMessageHandler(/* args */)
{
}

TestMessageHandler::~TestMessageHandler()
{
}

void TestMessageHandler::Handle(const Session *session, TestMessage *message)
{
    std::cout << message->id() << message->name() << message->content() << std::endl;
}

} // namespace wanderer