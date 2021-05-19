include(custom_module.cmake)

# include_directories("./")


WriteCustomModule(${CMAKE_CURRENT_SOURCE_DIR})
SetDefinitions(${CMAKE_CURRENT_SOURCE_DIR})

add_library(module STATIC custom_module.h custom_module.cpp)

AddLibraries(${CMAKE_CURRENT_SOURCE_DIR})
