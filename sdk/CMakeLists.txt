cmake_minimum_required(VERSION 3.8)

project(wanderer-sdk LANGUAGES C CXX)

option(BUILD_SHARED_LIBS "Dynamic libraries are compiled by default." ON)

set(SRC export.cpp export.h)

add_library(${PROJECT_NAME} ${SRC})