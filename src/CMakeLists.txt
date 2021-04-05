set(CMAKE_CXX_STANDARD 17)

set(OPENSSL_USE_STATIC_LIBS TRUE)
find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
    message("Openssl -Found: ${OPENSSL_VERSION} !!!")
endif(OPENSSL_FOUND)


include_directories(module libraries ${OPENSSL_INCLUDE_DIR})
include_directories("libraries/yaml-cpp/include")

add_subdirectory(libraries)
add_subdirectory(module)

# 获取所有的第三方库
get_property(LIBRARYIES GLOBAL PROPERTY libraries)

file(GLOB_RECURSE src "base/*.*"
    "inner_session/*.*"
    "network/*.*"
    "utility/*.*"
    "center/*.*"
    "login/*.*" 
    "gateway/*.*")

add_library(core ${src})

target_link_libraries(core ${LIBRARYIES} module ${OPNESSL_LIBRARY})