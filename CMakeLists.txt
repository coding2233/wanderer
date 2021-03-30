cmake_minimum_required(VERSION 3.8)

project(wanderer LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories("src")

# add_subdirectory(protocol)

add_subdirectory(src)

set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} core)