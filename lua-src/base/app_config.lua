-- App type
AppType_None = 0
AppType_Login = 1 << 0
AppType_Gateway = 1 << 1
AppType_DataBase = 1 << 2
AppType_Center = 1 << 3
AppType_Battle = 1 << 4
AppType_All = AppType_Login | AppType_Gateway | AppType_DataBase | AppType_Center | AppType_Battle

-- Actor address
ActorAddress_START_INDEX = 0
ActorAddress_ALL = -1
ActorAddress_LOGIN = -2
ActorAddress_CENTER = -3
ActorAddress_DATABASE = -4
ActorAddress_GATEWAY = -5
ActorAddress_CENTER_START_INDEX = -100


Actor_Scripts = {}
Actor_Scripts[AppType_Login] = {"actor_login",ActorAddress_LOGIN}
Actor_Scripts[AppType_Gateway] = {"actor_gateway",ActorAddress_GATEWAY}
Actor_Scripts[AppType_DataBase] = {"actor_database",ActorAddress_GATEWAY}


-- GLOBAL = 1 << 0
-- @brief Information that can be useful to back-trace certain events - mostly useful than debug logs.
TRACE = 1 << 1
--- @brief Informational events most useful for developers to debug application
DEBUG = 1 << 2
--- @brief Severe error information that will presumably abort application
FATAL = 1 <<3
--- @brief Information representing errors in application but application will keep running
ERROR  = 1<<4
--- @brief Useful when application has potentially harmful situations
WARNING = 1<<5
-- VERBOSE = 1<< 6
--- @brief Mainly useful to represent current progress of application
INFO = 1<<7
-- UNKNOWN = 1010