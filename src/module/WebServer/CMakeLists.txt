file(GLOB_RECURSE SRC *.h *.cpp *.c)

add_library(webserver ${SRC})
