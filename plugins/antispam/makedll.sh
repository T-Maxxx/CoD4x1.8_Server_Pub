#!/bin/bash

echo Compiling: release
g++ --std=c++17 -m32 -Wall -O1 -mtune=core2 -c *.cpp

echo Linking
g++ --std=c++17 -m32 -Wall -shared -o antispam.so *.o
echo Cleaning up
rm *.o

if [ $? -ne 0 ]
then
    echo "Compile failed!"
    exit 1
fi
