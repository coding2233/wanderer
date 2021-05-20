#ifndef __POOL_H__
#define __POOL_H__

#include <map>
#include <queue>
#include <string>
#include <utility>

#include "base/easylogging++.h"

namespace wanderer 
{
    template <class T>
    class Pool
    {
        std::queue<T*> pool_objects_;
    public:
        Pool()
        {}
        ~Pool()
        {}

        T* Pop()
        {
            T* object;
            if (pool_objects_.size()>0) 
            {
                object=pool_objects_.front();
                pool_objects_.pop();
            }
            else 
            {
                object=new T;
            }
            return object;
        }

        void Push(T *object)
        {
            pool_objects_.push(object);
        }

        int Size()
        {
            return pool_objects_.size();
        }
    };


}
#endif