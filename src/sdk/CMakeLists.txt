# # cmake_minimum_required(VERSION 3.8)

# # project(wanderer-sdk LANGUAGES C CXX)

# # option(BUILD_SHARED_LIBS "Dynamic libraries are compiled by default." ON)

# # set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread" )

# # add_subdirectory(../src/libraries)

# include_directories("./")
# include_directories("./network")
# include_directories("../")
# # include_directories("../src")
# # include_directories("../src/network")
# include_directories(${CMAKE_SOURCE_DIR})
# # include_directories("../src/libraries")
# # file(GLOB_RECURSE SHARE_SRC "../src/network/*.*" "../src/network/*.*")

# file(GLOB_RECURSE SRC export.cpp export.h "network/*.*")

# add_library(${PROJECT_NAME} ${SRC})

# # target_link_libraries(${PROJECT_NAME} ${libraries})