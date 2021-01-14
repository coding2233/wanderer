include(${CMAKE_CURRENT_SOURCE_DIR}/custom_module/custom_module.cmake)

# WriteCustomModule
WriteCustomModule(${CMAKE_CURRENT_SOURCE_DIR}/custom_module)

file(GLOB_RECURSE src *.cpp *.h)

add_library(core ${src})

target_link_libraries(core)
