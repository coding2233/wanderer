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
    #Organize the SDK header files
    set(sdk_include_path "${CMAKE_BINARY_DIR}/include")
    message("sdk_include_path: ${sdk_include_path}")
    file(MAKE_DIRECTORY "${sdk_include_path}")
    # Sdk-sdk header files
    file(MAKE_DIRECTORY "${sdk_include_path}/sdk")
    file(GLOB_RECURSE sdk_include_files "sdk/*.h")
    file(COPY ${sdk_include_files} DESTINATION "${sdk_include_path}/sdk")
    # Sdk-utility header files
    file(MAKE_DIRECTORY "${sdk_include_path}/utility")
    file(GLOB_RECURSE utility_include_files "utility/*.h")
    file(COPY ${utility_include_files} DESTINATION "${sdk_include_path}/utility")
    # Sdk-base header files
    file(MAKE_DIRECTORY "${sdk_include_path}/base")
    file(GLOB_RECURSE base_include_files "base/system.h" "base/app_config.h" "base/easylogging*.h")
    file(COPY ${base_include_files} DESTINATION "${sdk_include_path}/base")
    # Sdk-network header files
    file(MAKE_DIRECTORY "${sdk_include_path}/network")
    file(GLOB_RECURSE network_include_files "network/message.h" "network/circle_buffer.h")
    file(COPY ${network_include_files} DESTINATION "${sdk_include_path}/network")
    # Sdk-actor header files
    file(MAKE_DIRECTORY "${sdk_include_path}/actor")
    file(GLOB_RECURSE actor_include_files "actor/actor.h")
    file(COPY ${actor_include_files} DESTINATION "${sdk_include_path}/actor")
   
    # foreach(item in ${sdk_include})
    #     file(COPY ${item} DESTINATION "${sdk_include_path}")
    #     message("${item}")
    # endforeach()
    add_library(${SDK_NAME} SHARED ${sdk_src} )
  
    target_link_libraries(${SDK_NAME} ${link_libraries} module)  
endif(BUILD_SDK)