#!/usr/bin/bash

#build documentation 
#remark: launch from the root directory
cmake -S . -B docs/build -G Ninja
cmake --build docs/build --target doxygen > docs.log
