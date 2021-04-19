#!/bin/sh

SRC=/src
cd ${SRC}

BUILD=build/docker-build

cmake --no-warn-unused-cli -DWEBSERVER=OFF -DLUASCRIPT=OFF -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true -DCMAKE_TOOLCHAIN_FILE=${SRC}/cmake/linux_clang.cmake -S ${SRC} -B ${SRC}/${BUILD} && cmake --build ${SRC}/${BUILD} -j 10