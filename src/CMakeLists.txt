file(GLOB_RECURSE src *.cpp)

add_library(core ${src})

target_link_libraries(core protocol)
