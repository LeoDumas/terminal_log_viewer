#!/bin/sh

clear
echo "Building project"

if [ "$1" = "-rebuild" ]; then
    echo "Rebuilding: removing build directory"
    rm -rf build
fi

mkdir -p build
cd build
cmake -G Ninja ..
cmake --build .

echo "Build done"