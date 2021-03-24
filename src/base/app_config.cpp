#include "base/app_config.h"
namespace wanderer
{

AppConfig::AppConfig(int argc, char *args[])
{
    argc_ = argc;
    args_ = args;

    app_type_ = AppType_All;
    server_ip_= gate_ip_ = "127.0.0.1";
    server_port_ = gate_port_ = 2233;
    secret_key_ = "c6596580cc9c193d6b8a15becff9a31d";

    int index = 1;
    while (index < argc)
    {
        if (std::strcmp(args[index], "--type") == 0 || std::strcmp(args[index], "-t") == 0)
        {
            index++;
            SetAppType(args[index]);
        }
        else if (std::strcmp(args[index], "--server") == 0 || std::strcmp(args[index], "-s") == 0)
        {
            index++;
            SetSeverInfo(args[index]);
        }
        else if (std::strcmp(args[index], "--gate_server") == 0 || std::strcmp(args[index], "-g") == 0)
        {
            index++;
            SetGateInfo(args[index]);
        }
        else if (std::strcmp(args[index], "--secret") == 0 || std::strcmp(args[index], "-S") == 0)
        {
            index++;
            SetSecretKey(args[index]);
        }
        else if (std::strcmp(args[index], "--help") == 0 || std::strcmp(args[index], "-h") == 0)
        {
            ShowHelp();
            std::exit(EXIT_SUCCESS);
        }
        index++;
    }
}

AppConfig::~AppConfig()
{
}

void AppConfig::SetAppType(char *arg)
{
    if (std::strcmp(arg, "all") == 0)
    {
        app_type_ = AppType_All;
    }
    else if (std::strcmp(arg, "login") == 0)
    {
        app_type_ = AppType_Login;
    }
    else if (std::strcmp(arg, "gate") == 0)
    {
        app_type_ = AppType_Gate;
    }
    else if (std::strcmp(arg, "database") == 0)
    {
        app_type_ = AppType_DataBase;
    }
    else if (std::strcmp(arg, "center") == 0)
    {
        app_type_ = AppType_Center;
    }
    else if (std::strcmp(arg, "battle") == 0)
    {
        app_type_ = AppType_Battle;
    }
    else
    {
        Exit();
    }
}

void AppConfig::SetSeverInfo(char *arg)
{
    char *v = std::strtok(arg, ":");
    if (v == nullptr)
    {
        Exit();
    }
    server_ip_ = v;
    v = std::strtok(nullptr, ":");
    if (v == nullptr)
    {
        Exit();
    }
    server_port_ = atoi(v);
}

void AppConfig::SetGateInfo(char *arg)
{
    char *v = std::strtok(arg, ":");
    if (v == nullptr)
    {
        Exit();
    }
    gate_ip_ = v;
    v = std::strtok(nullptr, ":");
    if (v == nullptr)
    {
        Exit();
    }
    gate_port_ = atoi(v);
}

void AppConfig::SetSecretKey(char *arg)
{
    secret_key_ = arg;
}

void AppConfig::ShowHelp()
{
    std::cout << std::endl;

    std::cout << "-h,--help" << std::endl;
    std::cout << "\t"
              << "help info" << std::endl;

    std::cout << "-t,--type" << std::endl;
    std::cout << "\t"
              << "all,login,gate,database,center,battle" << std::endl;

    std::cout << "-S,--secret" << std::endl;
    std::cout << "\t"
              << "secret key,openssl rand -hex 16" << std::endl;

    std::cout << "-s,--server" << std::endl;
    std::cout << "\t"
              << "server address & port, e.g. 127.0.0.1:2233" << std::endl;

    std::cout << "-g,--gate_server" << std::endl;
    std::cout << "\t"
              << "gate server,e.g. 127.0.0.1:223" << std::endl;

    std::cout << std::endl;
}

void AppConfig::Exit()
{
    std::cout << "Enter --help to view help information" << std::endl;
    std::exit(EXIT_SUCCESS);
}

} // namespace wanderer