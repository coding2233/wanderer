file(GLOB_RECURSE SRC *.h *.cpp *.c)

message("${CMAKE_BUILD_RPATH}")
message("--------------------------------------------")

add_library(luascript STATIC ${SRC})

