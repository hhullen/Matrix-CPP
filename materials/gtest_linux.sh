#!/bin/bash

apt install g++
apt install libgtest-dev
apt install cmake
cd /usr/src/gtest
cmake CMakeLists.txt
make
cp *.a /usr/lib