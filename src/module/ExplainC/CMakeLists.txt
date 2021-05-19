file(GLOB_RECURSE SRC *.h *.cpp *.c)

add_library(explainc STATIC ${SRC})