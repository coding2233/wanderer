#include "base/app.h"
#include "actor/actor_module.h"

INITIALIZE_EASYLOGGINGPP

namespace wanderer
{

    int App::signal_flag_ = 0;

    App::App()
    {
        system_ = new System(&modules_);
    }

    App::~App()
    {
    }

    void App::Run(int argc, char *args[])
    {
        // std::cout.rdbuf(log_file.rdbuf());
        // //绑定操作信号
        // std::signal(SIGINT, App::SignalHandler);
        //外部参数
        AppConfig *app_config = new AppConfig(argc, args);
        System::app_config_ = app_config;

        //设置日志
        if (!app_config->log_path_.empty())
        {
            el::Configurations defaultConf;
            defaultConf.setToDefault();
            // 基于当前系统的当前日期/时间
            time_t now = time(0);
            tm *ltm = localtime(&now);
            std::string log_path = app_config->log_path_ + "/" + app_config->app_type_name_ + "_" + std::to_string(1900 + ltm->tm_year) + "_" + std::to_string(ltm->tm_mon + 1) + "_" + std::to_string(ltm->tm_mday) + ".log";
            defaultConf.setGlobally(el::ConfigurationType::Filename, log_path);
            el::Loggers::reconfigureLogger("default", defaultConf);
            el::Loggers::reconfigureAllLoggers(defaultConf);
        }

        //各种模块
        InitModule(app_config);
        Init();
        MainLoop();
        CleanUp();
    }

    void App::InitModule(AppConfig *app_config)
    {
        NetworkModule *network_module = new NetworkModule(system_);
        ActorModule *actor_module = new ActorModule(system_);

        CenterModule *center_module = nullptr;
        LoginModule *login_module = nullptr;
        GatewayModule *gateway_module = nullptr;

        switch (app_config->app_type_)
        {
        case AppType_All:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            // network_module->CreateInnerSession(AppType_Login, app_config->center_ip_.c_str(), app_config->center_port_);
            // network_module->CreateInnerSession(AppType_DataBase, app_config->center_ip_.c_str(), app_config->center_port_);
            // network_module->CreateInnerSession(AppType_Center, app_config->center_ip_.c_str(), app_config->center_port_);
            // network_module->CreateInnerSession(AppType_Battle, app_config->center_ip_.c_str(), app_config->center_port_);

            // gateway_module = new GatewayModule(system_);
            center_module = new CenterModule(system_);
            login_module = new LoginModule(system_);

            break;
        case AppType_Login:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            // network_module->CreateInnerSession(AppType_Login, app_config->center_ip_.c_str(), app_config->center_port_);

            login_module = new LoginModule(system_);
            break;
        case AppType_Gateway:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);

            gateway_module = new GatewayModule(system_);
            break;
        case AppType_DataBase:
            // network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            // network_module->CreateInnerSession(AppType_DataBase, app_config->center_ip_.c_str(), app_config->center_port_);
            break;
        case AppType_Center:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            // network_module->CreateInnerSession(AppType_Center, app_config->center_ip_.c_str(), app_config->center_port_);
            center_module = new CenterModule(system_);
            break;
        case AppType_Battle:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            // network_module->CreateInnerSession(AppType_Battle, app_config->center_ip_.c_str(), app_config->center_port_);
            break;
        default:
            break;
        }

        //Add modules to map
        AddModule(network_module);
        AddModule(center_module);
        AddModule(login_module);
        AddModule(gateway_module);
        AddModule(actor_module);

        //load custom module
        CustomModule custom_module(&modules_, system_);
    }

    void App::Init()
    {
        //遍历
        for (module_iter_ = modules_.begin(); module_iter_ != modules_.end(); module_iter_++)
        {
            module_iter_->second->OnInit();
        }

        //初始化完所有操作后，才进行内部通信的连接
        AppConfig *app_config = System::app_config_;
        NetworkModule *network_module = System::GetModule<NetworkModule>();
        if (app_config->app_type_ != AppType_Center)
        {
            network_module->CreateInnerSession(app_config->app_type_, app_config->center_ip_.c_str(), app_config->center_port_);
        }
    }

    void App::MainLoop()
    {
        while (signal_flag_ == 0)
        {
            int index = 0;
            for (module_iter_ = modules_.begin(); module_iter_ != modules_.end(); module_iter_++)
            {
                LOG(INFO) << "App::MainLoop  " << index++;
                module_iter_->second->OnUpdate();
            }
        }
    }

    void App::CleanUp()
    {
        for (module_iter_ = modules_.begin(); module_iter_ != modules_.end(); module_iter_++)
        {
            Module *module = module_iter_->second;
            module->OnClose();
            delete module;
        }
        modules_.clear();
    }

    void App::AddModule(Module *module)
    {
        if (module != nullptr)
        {
            modules_.insert(std::pair<std::string, Module *>(typeid(*module).name(), module));
        }
    }

} // namespace wanderer
