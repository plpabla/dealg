#! /bin/sh

cd build/ && cmake ..
if make; then 
    ./runTests
fi
