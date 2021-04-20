
# add_compile_definitions(_7ZIP_ST)

# add_definitions(-D _7ZIP_ST)

add_subdirectory(yaml-cpp)
add_subdirectory(openssl-cmake)
add_subdirectory(zlib)
# yaml include
# set(YAML_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/yaml-cpp/include")
# 设置第三方的头文件
# set_property(GLOBAL APPEND PROPERTY libraries-include ${YAML_INCLUDE})


# easy logging
# add_library(easy-logging "easyloggingpp/*.*")

# aux_source_directory("./lzma" LZMA_SRC)
# set(LZMA_SRC ./lzma/Alloc.c ./lzma/Alloc.h ./lzma/LzFind.c ./lzma/LzFind.h ./lzma/LzFindMt.c ./lzma/LzFindMt.h ./lzma/LzmaDec.c ./lzma/LzmaDec.h)
# add_library(lzma ${LZMA_SRC})

set(openssl-libs ssl crypto)
if(WIN32)
    set(openssl-lib-dir ${CMAKE_CURRENT_SOURCE_DIR}/libs-binary/openssl)
    set(openssl-libs  ${openssl-lib-dir}/win64/libcrypto.dll.a ${openssl-lib-dir}/win64/libssl.dll.a)
elseif(UNIX)
    set(openssl-libs ssl crypto)
endif()

# 设置第三方的库
set_property(GLOBAL APPEND PROPERTY libraries yaml-cpp zlib ${openssl-libs})

