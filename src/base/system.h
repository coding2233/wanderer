#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#include <map>

namespace wanderer
{

class Module;

class System
{
private:
    std::map<std::string, Module *> *modules_;

public:
    System(std::map<std::string, Module *> *modules);
    ~System();

    template <class T>
    T *GetModule()
    {
        auto iter = modules_->find(typeid(T).name());
        if (iter != modules_->end())
        {
            return dynamic_cast<T *>(iter->second);
        }
        return nullptr;
    }
};
} // namespace wanderer

#endif