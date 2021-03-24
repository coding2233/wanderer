#!/bin/sh

export SRC=/src

cd ${SRC}

ls ${SRC}

cmake --no-warn-unused-cli -DWEBSERVER=ON -DLUASCRIPT=ON -DCMAKE_TOOLCHAIN_FILE=${SRC}/cmake/linux_clang.cmake -S ${SRC} -B ${SRC}/build && cmake --build ${SRC}/build