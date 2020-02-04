#ifndef __REFLECTOR_H__
#define __REFLECTOR_H__

#include <map>
#include <memory>
#include <functional>

#define FUNC std::function<void *(void)>
//#define REGISTER(CLASS_NAME)

class Reflector
{
private:
    //函数类
    static std::map<std::string, FUNC> class_function_map_;
    // std::shared_ptr
public:
    Reflector(/* args */);
    ~Reflector();

    //注册类名
    static void Register(const std::string &class_name, FUNC create_function);
    //创建对象
    static void Create(const std::string &class_name);
};

#endif