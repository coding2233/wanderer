set(CMAKE_CXX_STANDARD 17)
set(CMAKE_SYSTEM_NAME linux)

# set(OPENSSL_USE_STATIC_LIBS TRUE)
# set(OPENSSL_ROOT_DIR /usr/bin/openssl)

# find_package(OpenSSL REQUIRED)
# if(OPENSSL_FOUND)
#     message("Openssl -Found: ${OPENSSL_VERSION} ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBRARIES}!!!")
# endif(OPENSSL_FOUND)


# set(OPENSSL_INCLUDE_DIR /usr/include)
# set(OPENSSL_LIBRARIES /usr/lib/x86_64-linux-gnu/libssl.a;/usr/lib/x86_64-linux-gnu/libcrypto.a;)

include_directories(module libraries)
include_directories(libraries/yaml-cpp/include)
include_directories(libraries/lzma)

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

target_link_libraries(core ${LIBRARYIES} module)