#ifndef __MODULE_H__
#define __MODULE_H__

namespace wanderer
{

class Module
{
protected:
    /* data */

protected:
public:
    Module();
    ~Module();

    //初始化
    virtual void OnInit() = 0;
    //循环
    virtual void OnUpdate() = 0;
    //关闭
    virtual void OnClose() = 0;
};
} // namespace wanderer
#endif