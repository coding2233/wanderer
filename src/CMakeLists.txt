set(CMAKE_CXX_STANDARD 17)

include_directories(module libraries)
include_directories("libraries/yaml-cpp/include")

add_subdirectory(libraries)
add_subdirectory(module)

# 获取所有的第三方库
get_property(LIBRARYIES GLOBAL PROPERTY libraries)

file(GLOB_RECURSE src "base/*.*"
    "inner_session/*.*"
    "network/*.*"
    "utility/*.*"
    "center/*.*"
    "login/*.*" 
    "gateway/*.*")

add_library(core ${src})

target_link_libraries(core ${LIBRARYIES} module)