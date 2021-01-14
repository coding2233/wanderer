file(GLOB_RECURSE src *.cpp *.h)

add_library(core ${src})

target_link_libraries(core)
