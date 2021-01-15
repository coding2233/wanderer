set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_CURRENT_SOURCE_DIR}/custom_module/custom_module.cmake)

# include_directories(${CMAKE_CURRENT_SOURCE_DIR}/custom_module)

# WriteCustomModule
WriteCustomModule(${CMAKE_CURRENT_SOURCE_DIR}/custom_module)
# SetDefinitions
SetDefinitions(${CMAKE_CURRENT_SOURCE_DIR}/custom_module)

file(GLOB_RECURSE src *.cpp *.h *.c)

add_library(core ${src})

target_link_libraries(core)
