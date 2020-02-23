#include "utility/utility.h"

#ifdef __cplusplus
extern "C"
{
#endif
    int CharPointer2Int(const char *data)
    {
        int result = 0;

        for (int i = 0; i < 4; i++)
        {
            result |= (data[i] & 0xFF) << ((3 - i) * 8);
        }
        return result;
    }

#ifdef __cplusplus
}
#endif
