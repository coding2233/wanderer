
set(CMAKE_CXX_STANDARD 17)

# set(CMAKE_SYSTEM_NAME linux)

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
# include_directories(libraries/openssl-include)
include_directories(libraries/openssl-cmake/include)
# include_directories(libraries/lzma)
include_directories(libraries/zlib)
include_directories(libraries/zlib/*)
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_BINARY_DIR}/src/libraries/openssl-cmake/include)

if(WIN32)
# include_directories("/usr/x86_64-w64-mingw32/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /DWIN32_LEAN_AND_MEAN")
# include_directories("/usr/include")
endif(WIN32)

add_subdirectory(libraries)
add_subdirectory(module)

# 获取所有的第三方库
# get_property(LIBRARYIES GLOBAL PROPERTY libraries)

file(GLOB_RECURSE base_src
    "base/*.*"
    "network/*.*"
    "utility/*.*"   
    "actor/*.*" 
)

file(GLOB_RECURSE src
    "center/*.*"
    "login/*.*" 
    "gateway/*.*"
    "database/*.*"
    )

if(BUILD_EXEC)
    add_definitions("-DBUILD_EXEC")
endif(BUILD_EXEC)

if(BUILD_SDK)
    include_directories(sdk)
    add_definitions("-DBUILD_SDK")
endif(BUILD_SDK)

set(openssl_libs ssl crypto)
set(link_libraries ${openssl_libs} zlib yaml-cpp)

if(BUILD_EXEC)
    add_library(core STATIC ${base_src} ${src})
    target_link_libraries(core ${link_libraries} module)
endif(BUILD_EXEC)

option(BUILD_SDK "The SDK is released simultaneously by default." ON)
if(BUILD_SDK)
    set(SDK_NAME "${PROJECT_NAME}-sdk")
    file(GLOB_RECURSE sdk_src "sdk/*.*"
                            "utility/*.*"
                            "actor/actor.*"
                            "base/system.*"
                            "base/app_config.*"
                            "base/easylogging*.*"
                            "network/message.*"
                            "network/circle_buffer.*"
    )

    include(../cmake/arrange.sdk.include.cmake)
   
    # foreach(item in ${sdk_include})
    #     file(COPY ${item} DESTINATION "${sdk_include_path}")
    #     message("${item}")
    # endforeach()
    add_library(${SDK_NAME} SHARED ${sdk_src} )
  
    target_link_libraries(${SDK_NAME} ${link_libraries} module)  
endif(BUILD_SDK)