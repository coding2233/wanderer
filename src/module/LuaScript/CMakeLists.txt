file(GLOB_RECURSE SRC *.h *.cpp *.c)

add_library(luascript STATIC ${SRC})
