#!/bin/bash

BUILD_DIR=build
cd $BUILD_DIR
make test ARGS="-VV"
