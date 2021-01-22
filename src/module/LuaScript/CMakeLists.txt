include_directories("${CMAKE_CURRENT_SOURCE_DIR}/lua-5.4.2/src")

file(GLOB_RECURSE SRC *.h *.cpp *.c)

add_library(luascript ${SRC})
