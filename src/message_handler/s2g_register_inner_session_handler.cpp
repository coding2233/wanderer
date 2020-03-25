#include "message_handler/s2g_register_inner_session_handler.h"

namespace wanderer
{

S2G_RegisterInnerSessionHandler::S2G_RegisterInnerSessionHandler(/* args */)
{
}

S2G_RegisterInnerSessionHandler::~S2G_RegisterInnerSessionHandler()
{
}

void S2G_RegisterInnerSessionHandler::Handle(const Session *session, S2G_RegisterInnerSession *message)
{
    std::cout << "s2g register inner session: " <<"["<< message->name()<<"] " << message->secret() << std::endl;
}

} // namespace wanderer
