// #ifndef __REFLECTOR_H__
// #define __REFLECTOR_H__

// #include <map>
// #include <memory>
// #include <functional>

// namespace wanderer
// {
// #define FUNC std::function<void *()>

// class Reflector
// {
// private:
//     //函数类
//     std::map<std::string, FUNC> class_function_map_;

// public:
//     Reflector(/* args */);
//     ~Reflector();

//     static Reflector *GetInstance()
//     {
//         static Reflector instance;
//         return &instance;
//     }

//     //注册类名
//     void Register(const std::string &class_name, FUNC create_function);
//     //创建对象
//     void Create(const std::string &class_name);
// };
// } // namespace wanderer

// #endif