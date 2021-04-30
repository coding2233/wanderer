#ifndef __MODULE_H__
#define __MODULE_H__

#include "base/easylogging++.h"
#include "base/system.h"

namespace wanderer
{

    class Module
    {

    private:
        /* data */
        System *system_;

    protected:
        System *GetSystem() const;

    public:
        Module(System *system);
        virtual ~Module();

        //初始化
        virtual void OnInit() = 0;
        //循环
        virtual void OnUpdate() = 0;
        //关闭
        virtual void OnClose() = 0;
      
    };
} // namespace wanderer
#endif