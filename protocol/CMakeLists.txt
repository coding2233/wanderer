file(GLOB_RECURSE src *.cc)

add_library(protocol ${src})

target_link_libraries(protocol libprotobuf)
