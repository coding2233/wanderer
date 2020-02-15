#ifndef __MODULE_H__
#define __MODULE_H__

namespace wanderer
{
class App;

class Module
{
protected:
    /* data */

protected:
public:
    Module();
    ~Module();

    //初始化
    virtual void OnInit();
    //循环
    virtual void OnUpdate();
    //关闭
    virtual void OnClose();
};
} // namespace wanderer
#endif