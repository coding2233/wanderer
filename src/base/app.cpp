#include "base/app.h"

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
        // 基于当前系统的当前日期/时间
        time_t now = time(0);
        tm* ltm = localtime(&now);
        std::string dir_name = "log";
        if (!std::filesystem::is_directory(dir_name))
        {
            std::filesystem::create_directory(dir_name);
        }
        std::string log_path = dir_name+"/"+std::to_string(1900 + ltm->tm_year) + "_" + std::to_string(ltm->tm_mon+1) + "_" + std::to_string(ltm->tm_mday) + "_log.txt";
        //auto file_path = std::filesystem::absolute(log_path);
        //std::cout to log file
        std::ofstream log_file(log_path);
        std::cout.rdbuf(log_file.rdbuf());
        //绑定操作信号
        std::signal(SIGINT, App::SignalHandler);
        //外部参数
        AppConfig *app_config = new AppConfig(argc, args);
        System::app_config_ = app_config;
        //各种模块
        InitModule(app_config);
        Init();
        MainLoop();
        CleanUp();
    }

    void App::InitModule(AppConfig *app_config)
    {
        NetworkModule *network_module = new NetworkModule(system_);
        InnerSessionModule *inner_session_module = new InnerSessionModule(system_);

        LoginModule* login_module = nullptr;
        GateModule* gate_module=nullptr;

        switch (app_config->app_type_)
        {
        case AppType_All:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            network_module->CreateInnerSession(AppType_Login, app_config->gate_ip_.c_str(), app_config->gate_port_);
            network_module->CreateInnerSession(AppType_DataBase, app_config->gate_ip_.c_str(), app_config->gate_port_);
            network_module->CreateInnerSession(AppType_Center, app_config->gate_ip_.c_str(), app_config->gate_port_);
            network_module->CreateInnerSession(AppType_Battle, app_config->gate_ip_.c_str(), app_config->gate_port_);

            gate_module = new GateModule(system_);
            login_module = new LoginModule(system_);

            break;
        case AppType_Login:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            network_module->CreateInnerSession(AppType_Login, app_config->gate_ip_.c_str(), app_config->gate_port_);
            
            login_module = new LoginModule(system_);
            break;
        case AppType_Gate:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            
            gate_module = new GateModule(system_);
            break;
        case AppType_DataBase:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            network_module->CreateInnerSession(AppType_DataBase, app_config->gate_ip_.c_str(), app_config->gate_port_);
            break;
        case AppType_Center:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            network_module->CreateInnerSession(AppType_Center, app_config->gate_ip_.c_str(), app_config->gate_port_);
            break;
        case AppType_Battle:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            network_module->CreateInnerSession(AppType_Battle, app_config->gate_ip_.c_str(), app_config->gate_port_);
            break;
        default:
            break;
        }

        //Add modules to map
        AddModule(network_module);
        AddModule(inner_session_module);
        AddModule(gate_module);

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
    }

    void App::MainLoop()
    {
        while (signal_flag_==0)
        {
            for (module_iter_ = modules_.begin(); module_iter_ != modules_.end(); module_iter_++)
            {
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

    void App::AddModule(Module* module)
    {
        if (module!=nullptr)
        {
            modules_.insert(std::pair<std::string, Module*>(typeid(*module).name(), module));
        }
    }

} // namespace wanderer
