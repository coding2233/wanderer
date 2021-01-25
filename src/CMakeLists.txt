set(CMAKE_CXX_STANDARD 17)

include_directories(module)

add_subdirectory(module)

file(GLOB_RECURSE src "base/*.*"
    "inner_session/*.*"
    "network/*.*"
    "utility/*.*"
    "login/*.*" 
    "gate/*.*")

add_library(core ${src})

target_link_libraries(core module)
