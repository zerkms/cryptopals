#!/bin/bash

BUILD_DIR=$(readlink -f ./build)
CMAKE_DIR=$(readlink -f ./projects/CMake)

mkdir $BUILD_DIR
cd $BUILD_DIR

cmake $CMAKE_DIR
make -j3
