#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <map>
#include <string>

#include "base/app_config.h"

namespace wanderer
{
    class Module;

#define VERSION "0.1.0"

    class System
    {
    private:
        static std::map<std::string, Module *> *modules_;

    public:
        System(std::map<std::string, Module *> *modules);
        ~System();

        template <class T>
        static T *GetModule()
        {
            auto iter = modules_->find(typeid(T).name());
            if (iter != modules_->end())
            {
                return dynamic_cast<T *>(iter->second);
            }
            return nullptr;
        }

        static AppConfig *app_config_;
    };
} // namespace wanderer

#endif
