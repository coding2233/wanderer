#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__

#include <cstring>
#include <iostream>
#include <list>

namespace wanderer
{

enum AppType
{
    //登录服务器
    kLogin = 1 << 0,
    //网关服务器
    kGate = 1 << 1,
    //数据库服务器
    kDataBase = 1 << 2,
    //中心服务器
    kCenter = 1 << 3,
    //战场服务器
    kBattle = 1 << 4,
    //集所有服务器为一体
    kAll = kLogin | kGate | kDataBase | kCenter | kBattle
};

class AppConfig
{
private:
    //显示帮助
    void ShowHelp();
    //设置app类型
    void SetAppType(char* arg);
    //设置服务器的信息
    void SetSeverInfo(char* arg);
    //设置网关服务器的信息
    void SetGateInfo(char* arg);
    //设置密钥
    void SetSecretKey(char* arg);
    //退出程序
    void Exit();
public:
    AppConfig(int argc, char *args[]);
    ~AppConfig();
    //类型
    AppType app_type_;
    //密钥
    std::string secret_key_;
    //服务器ip
    std::string server_ip_;
    //服务器的端口
    int server_port_;
    //网关服务器ip
    std::string gate_ip_;
    //网关服务器的端口
    int gate_port_;
};
} // namespace wanderer

#endif