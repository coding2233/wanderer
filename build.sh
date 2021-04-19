#!/usr/bin/bash

export SRC="./"
export BUILD="build"
export OPENSSL_BUILD_VERSION="1.1.1k"
export OPENSSL_BUILD_HASH="892a0875b9872acd04a9fde79b1f943075d5ea162415de3047c327df33fbaee5"

cmake --no-warn-unused-cli -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true -DCMAKE_TOOLCHAIN_FILE=${SRC}/cmake/mingw64_windows.cmake -DBUILD_EXEC=OFF -DWEBSERVER=OFF -DLUASCRIPT=OFF -S ${SRC} -B ${SRC}/${BUILD} && cmake --build ${SRC}/${BUILD} -j 10


#-DCMAKE_TOOLCHAIN_FILE=${SRC}/cmake/mingw64_windows.cmake
#-DBUILD_EXEC=OFF
