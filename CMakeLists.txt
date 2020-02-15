cmake_minimum_required(VERSION 3.0)

project(wanderer)

set(CMAKE_CXX_STANDARD 17)

include_directories("include" "protocol")

add_subdirectory(library)

add_subdirectory(protocol)

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} core)