#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <iostream>
#include <string>

#ifdef __cplusplus
extern "C"
{
#endif
    //char* 转int
    int CharPointer2Int(const char *data);
    //int转char*
    void Int2CharPointer(char *data, int value);

#ifdef __cplusplus
}
#endif

#endif
