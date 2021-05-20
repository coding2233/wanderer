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