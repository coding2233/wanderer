#ifndef __MODULE_H__
#define __MODULE_H__

class Module
{
private:
    /* data */
public:
    Module(/* args */);
    ~Module();

    //初始化
    virtual void OnInit();
    //循环
    virtual void OnUpdate();
    //关闭
    virtual void OnClose();
};

#endif