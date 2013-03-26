#!/bin/sh

echo "Preparing default compiler build"
(
    [ -d build-default ] || mkdir build-default
    cd build-default && cmake -DCMAKE_BUILD_TYPE=Release .. && make -j8
)

# Conditionally build for clang
if command -v clang &>/dev/null;
then
    echo "Preparing clang compiler build"
    (
        [ -d build-clang ] || mkdir build-clang
        cd build-clang && CC=$(which clang) CXX=$(which clang++) cmake -DCMAKE_BUILD_TYPE=Release .. && make -j8
    )
fi
