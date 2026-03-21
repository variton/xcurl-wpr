#!/usr/bin/bash

#format
# find . \
#   -type f \( -name "*.p" -o -name "*.h" \) \
#   -not -path "./build/*" \
#   -not -path "./.git/*" \
#   -not -path "./third_party/*" \
#   -exec clang-format -i {} +

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

#launch test coverage

#launch integration tests

#gather some metric
#generate report
