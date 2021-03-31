#include "base/app_config.h"
namespace wanderer
{
    AppConfig::AppConfig(int argc, char *args[])
    {

        app_type_ = AppType_None;
        server_ip_ = center_ip_ = "127.0.0.1";
        server_port_ = center_port_ = 12233;
        secret_key_ = "c6596580cc9c193d6b8a15becff9a31d";

        bool has_config = false;

        int index = 1;
        while (index < argc)
        {
            if (std::strcmp(args[index], "--config") == 0 || std::strcmp(args[index], "-c") == 0)
            {
                index++;
                SetConfig(args[index]);
                break;
            }
            // else if (std::strcmp(args[index], "--type") == 0 || std::strcmp(args[index], "-t") == 0)
            // {
            //     index++;
            //     SetAppType(args[index]);
            // }
            // else if (std::strcmp(args[index], "--server") == 0 || std::strcmp(args[index], "-s") == 0)
            // {
            //     index++;
            //     SetSeverInfo(args[index]);
            // }
            // else if (std::strcmp(args[index], "--gateway") == 0 || std::strcmp(args[index], "-g") == 0)
            // {
            //     index++;
            //     SetGateInfo(args[index]);
            // }
            // else if (std::strcmp(args[index], "--secret") == 0 || std::strcmp(args[index], "-S") == 0)
            // {
            //     index++;
            //     SetSecretKey(args[index]);
            // }
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

    void AppConfig::SetConfig(char *arg)
    {
        YAML::Node config = YAML::LoadFile(arg)["service"];

        service_config_ = config;

        if (config["log-path"].IsDefined())
        {
            log_path_ = config["log-path"].as<std::string>();
        }

        if (config["type"].IsDefined())
        {
            auto server_type = config["type"].as<std::string>().c_str();
            SetAppType(server_type);
        }

        if (config["server"].IsDefined())
        {
            server_ip_ = config["server"].as<std::string>();
        }

        if (config["port"].IsDefined())
        {
            server_port_ = config["port"].as<int>();
        }

        if (config["secret"].IsDefined())
        {
            secret_key_ = config["secret"].as<std::string>();
        }

        if (config["secret"].IsDefined())
        {
            secret_key_ = config["secret"].as<std::string>();
        }

        if (config["center"].IsDefined())
        {
            center_ip_ = config["center"]["server"].as<std::string>();
            center_port_ = config["center"]["port"].as<int>();
        }

        // for (YAML::const_iterator it = config.begin(); it != config.end(); it++)
        // {
        //     argc_++;
        //     std::cout << it->second.as<std::string>() << std::endl;
        // }
    }

    void AppConfig::SetAppType(const char *arg)
    {
        app_type_name_ = arg;

        if (std::strcmp(arg, "all") == 0)
        {
            app_type_ = AppType_All;
        }
        else if (std::strcmp(arg, "login") == 0)
        {
            app_type_ = AppType_Login;
        }
        else if (std::strcmp(arg, "gateway") == 0)
        {
            app_type_ = AppType_Gateway;
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

    void AppConfig::ShowHelp()
    {
        std::cout << std::endl;

        std::cout << "-h,--help" << std::endl;
        std::cout << "\t"
                  << "help info" << std::endl;

        std::cout << "-t,--type" << std::endl;
        std::cout << "\t"
                  << "all,login,gateway,database,center,battle" << std::endl;

        std::cout << "-S,--secret" << std::endl;
        std::cout << "\t"
                  << "secret key,openssl rand -hex 16" << std::endl;

        std::cout << "-s,--server" << std::endl;
        std::cout << "\t"
                  << "server address & port, e.g. 127.0.0.1:2233" << std::endl;

        std::cout << "-g,--gateway" << std::endl;
        std::cout << "\t"
                  << "gateway server,e.g. 127.0.0.1:223" << std::endl;

        std::cout << "-c,--config" << std::endl;
        std::cout << "\t"
                  << "A YAML file that supports the above parameters." << std::endl;

        std::cout << std::endl;
    }

    void AppConfig::Exit()
    {
        std::cout << "Enter --help to view help information" << std::endl;
        std::exit(EXIT_SUCCESS);
    }

} // namespace wanderer