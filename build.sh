#!/usr/bin/bash

export SRC="./"
export BUILD="build"

cmake --no-warn-unused-cli -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true -DBUILD_EXEC=ON -DWEBSERVER=OFF -DLUASCRIPT=OFF -S ${SRC} -B ${SRC}/${BUILD} && cmake --build ${SRC}/${BUILD} -j 10


#-DCMAKE_TOOLCHAIN_FILE=${SRC}/cmake/mingw64_windows.cmake
#-DBUILD_EXEC=OFF
