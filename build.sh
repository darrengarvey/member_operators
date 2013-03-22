#!/bin/sh

echo "Preparing default compiler build"
(
    [ -d build ] || mkdir build
    cd build && cmake .. && make -j8
)
echo "Preparing clang compiler build"
(
    [ -d build-clang ] || mkdir build-clang
    cd build-clang && CC=$(which clang) CXX=$(which clang++) cmake .. && make -j8
)
