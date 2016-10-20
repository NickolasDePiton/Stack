#!/bin/bash

BUILD_FLAGS=(
    -DCMAKE_CXX_FLAGS=-mmacosx-version-min=10.11.5
)
BUILD_DIR=build
mkdir -p $BUILD_DIR && cd $BUILD_DIR && \
cmake ${BUILD_FLAGS[@]} -DGLOBAL_PROJECT_NAME=$1 ../
make
