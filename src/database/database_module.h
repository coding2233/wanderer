#ifndef __DATABASE_MODULE_H__
#define __DATABASE_MODULE_H__

#include "actor/actor_module.h"
#include "base/module.h"
#include "database/actor_database.h"

namespace wanderer
{
    class DatabaseModule : public Module
    {
    private:
        /* data */
    public:
        DatabaseModule(System *system);
        ~DatabaseModule();

        //初始化函数
        void OnInit() override;
        //循环
        void OnUpdate() override;
        //关闭
        void OnClose() override;
    };
}

#endif