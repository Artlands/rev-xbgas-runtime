#!/bin/bash

if [ -d build ]; then
    rm -rf build
fi

if [ -d include ]; then
    rm -rf include
fi

if [ -d lib ]; then
    rm -rf lib
fi

mkdir build && cd build

cmake .. -DBUILD_COLLECTIVE_TESTING=ON \
         -DBUILD_DOCUMENTATION=OFF \
         -DCMAKE_INSTALL_PREFIX=$XBGAS_RUNTIME

make -j
make install