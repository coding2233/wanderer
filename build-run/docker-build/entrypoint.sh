#!/bin/sh

SRC=/src
cd ${SRC}

BUILD=build/docker-build

cmake --no-warn-unused-cli -DBUILD_EXEC=OFF -DBUILD_SDK=ON -DWEBSERVER=OFF -DLUASCRIPT=OFF -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true -DCMAKE_TOOLCHAIN_FILE=${SRC}/cmake/mingw64_windows.cmake -S ${SRC} -B ${SRC}/${BUILD} && cmake --build ${SRC}/${BUILD} -j 10
        