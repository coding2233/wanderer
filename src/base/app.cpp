#include "base/app.h"

namespace wanderer
{

    App::App()
    {
        system_ = new System(&modules_);
    }

    App::~App()
    {
    }

    void App::Run(int argc, char *args[])
    {
        AppConfig *app_config = new AppConfig(argc, args);

        InitModule(app_config);
        Init();
        MainLoop();
        CleanUp();
    }

    void App::InitModule(AppConfig *app_config)
    {
        NetworkModule *network_module = new NetworkModule(system_);
        InnerSessionModule *inner_session_module = new InnerSessionModule(system_);
        //GateModule* gate_module=nullptr;

        switch (app_config->app_type_)
        {
        case AppType_All:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            network_module->CreateInnerSession(AppType_Login, app_config->gate_ip_.c_str(), app_config->gate_port_);
            network_module->CreateInnerSession(AppType_DataBase, app_config->gate_ip_.c_str(), app_config->gate_port_);
            network_module->CreateInnerSession(AppType_Center, app_config->gate_ip_.c_str(), app_config->gate_port_);
            network_module->CreateInnerSession(AppType_Battle, app_config->gate_ip_.c_str(), app_config->gate_port_);

            //gate_module = new GateModule(system_);
            //modules_.insert(std::pair<std::string, Module*>(typeid(*gate_module).name(), gate_module));

            break;
        case AppType_Login:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            network_module->CreateInnerSession(AppType_Login, app_config->gate_ip_.c_str(), app_config->gate_port_);
            break;
        case AppType_Gate:
            network_module->CreateServer(app_config->server_ip_.c_str(), app_config->server_port_);
            //gate_module = new GateModule(system_);
            //modules_.insert(std::pair<std::string, Module*>(typeid(*gate_module).name(), gate_module));
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

        modules_.insert(std::pair<std::string, Module *>(typeid(*network_module).name(), network_module));
        modules_.insert(std::pair<std::string, Module *>(typeid(*inner_session_module).name(), inner_session_module));

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
        while (true)
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
} // namespace wanderer
