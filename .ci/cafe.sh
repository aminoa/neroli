#!/bin/bash -ex

#  This must run inside the devkitPro devkitPPC environment

mkdir -p build && cd build
cmake .. -G Ninja \
    -DCMAKE_TOOLCHAIN_FILE=/opt/devkitpro/cmake/WiiU.cmake \
    -DCMAKE_BUILD_TYPE=Release
ninja
