
add_subdirectory(yaml-cpp)

# yaml include
# set(YAML_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include")
# 设置第三方的头文件
set_property(GLOBAL APPEND PROPERTY libraries-include ${YAML_INCLUDE})
# 设置第三方的库
set_property(GLOBAL APPEND PROPERTY libraries yaml-cpp)

