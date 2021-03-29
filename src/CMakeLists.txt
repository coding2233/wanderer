set(CMAKE_CXX_STANDARD 17)

include_directories(libraries module)
include_directories("libraries/yaml-cpp/include")

add_subdirectory(libraries)
add_subdirectory(module)


# 获取第三方的头文件
get_property(LIBRARYIES_INCLUDE GLOBAL PROPERTY libraries-include)


message("------------------------------"${LIBRARYIES_INCLUDE})

# 获取所有的第三方库
get_property(LIBRARYIES GLOBAL PROPERTY libraries)

file(GLOB_RECURSE src "base/*.*"
    "inner_session/*.*"
    "network/*.*"
    "utility/*.*"
    "login/*.*" 
    "gate/*.*")

add_library(core ${src})

target_link_libraries(core ${LIBRARYIES} module)