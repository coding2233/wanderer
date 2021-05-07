#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <cstring>
#include <iostream>
#include <list>

#include "yaml-cpp/yaml.h"

namespace wanderer
{
    enum AppType_ : char
    {
        //没有服务器类型
        AppType_None = 0,
        //登录服务器
        AppType_Login = 1 << 0,
        //网关服务器
        AppType_Gateway = 1 << 1,
        //数据库服务器
        AppType_DataBase = 1 << 2,
        //中心服务器
        AppType_Center = 1 << 3,
        //战场服务器
        AppType_Battle = 1 << 4,
        //集所有服务器为一体
        AppType_All = AppType_Login | AppType_Gateway | AppType_DataBase | AppType_Center | AppType_Battle,
    };

    class AppConfig
    {
    private:
        //显示帮助
        void ShowHelp();
        //设置配置文件
        void SetConfig(char *arg);
        //设置app类型
        void SetAppType(const char *arg);
        //退出程序
        void Exit();

    public:
        AppConfig(int argc, char *args[]);
        ~AppConfig();
        //类型名称
        std::string app_type_name_;
        //类型
        AppType_ app_type_;
        //密钥
        std::string secret_key_;
        //服务器ip
        std::string server_ip_;
        //服务器的端口
        int server_port_;
        //中间服务器ip
        std::string center_ip_;
        //中间服务器的端口
        int center_port_;
        //日志文件
        std::string log_path_;
        //rsa私钥
        std::string rsa_private_key;
        //rsa公钥
        std::string rsa_public_key;
        //服务的配置文件
        YAML::Node service_config_;
    };
} // namespace wanderer

#endif