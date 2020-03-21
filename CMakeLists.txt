cmake_minimum_required(VERSION 3.0)

project(wanderer)

set(CMAKE_CXX_STANDARD 17)

include_directories("src" "protocol")

add_subdirectory(library)

add_subdirectory(protocol)

add_subdirectory(src)

set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} core)