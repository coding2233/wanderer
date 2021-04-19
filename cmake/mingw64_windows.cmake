# 设置交叉编译的目标操作为windows
set(CMAKE_SYSTEM_NAME Windows)

# 指定c/c++编译器
SET(CMAKE_C_COMPILER  /usr/bin/x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/x86_64-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER /usr/bin/x86_64-w64-mingw32-windres)

# 指定编译目标操作系统版本时的搜索根路径
SET(CMAKE_FIND_ROOT_PATH  /usr/x86_64-w64-mingw32 )

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)