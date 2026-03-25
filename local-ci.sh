#!/usr/bin/bash

BUILD_DIR="build/debug"
#launch test if test-xcurl exits

#launch unit tests
cd $BUILD_DIR
ctest --output-on-failure -j `nproc` 

#launch quality tests
cd $LAB 

#run quality test for xcurl impl
valgrind --leak-check=full ./bin/test_xcurl

#run quality test for xcurl_global impl
valgrind --leak-check=full ./bin/test_xcurl_global

#run quality test for test_utils
valgrind --leak-check=full ./bin/test_utils

#run quality test for test_xcgen
valgrind --leak-check=full ./bin/test_xcgen

#launch clang formating
clang-format -i src/**/*.cpp include/**/*.h test/*.cpp

#launch test coverage and generate html report
cmake --build $BUILD_DIR --target coverage

#launch integration tests

#gather some metric

#build documentation 
#remark: launch from the root directory
cmake -S . -B docs/build -G Ninja
cmake --build docs/build --target doxygen > docs.loggenerate
