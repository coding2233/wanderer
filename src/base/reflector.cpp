// #include "base/reflector.h"
// namespace wanderer
// {
// Reflector::Reflector(/* args */)
// {
// }

// Reflector::~Reflector()
// {
// }

// void Reflector::Register(const std::string &class_name, FUNC create_function)
// {
//     class_function_map_.insert(std::pair(class_name, create_function));
// }

// void Reflector::Create(const std::string &class_name)
// {
//     auto iter = class_function_map_.find(class_name);
//     if (iter != class_function_map_.end())
//     {
//         iter->second();
//         /* code */
//     }
// }
// }