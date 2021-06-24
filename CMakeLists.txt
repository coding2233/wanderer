cmake_minimum_required(VERSION 3.8)

project(wanderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_EXEC "The Publisher executes the program." ON)

include_directories("src")

# add_subdirectory(protocol)

add_subdirectory(src)

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )
file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/")
if (BUILD_EXEC)
    add_executable(${PROJECT_NAME} main.cpp)
    target_link_libraries(${PROJECT_NAME} core)
endif(BUILD_EXEC)