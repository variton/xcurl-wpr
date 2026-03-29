#!/usr/bin/bash

BUILD_DIR="build/debug"
#launch test if test-xcurl exits

#launch unit tests
cd $BUILD_DIR
ctest --output-on-failure -j `nproc` 

#launch quality tests
cd $LAB 

#run quality test for all tests in bin
REPORT_DIR="valgrind-reports"
mkdir -p "$REPORT_DIR"

counter=1

for file in ./bin/test_*; do
  if [[ -x "$file" && -f "$file" ]]; then
    name=$(basename "$file")
    report_file="$REPORT_DIR/report_${counter}_${name}.xml"

    echo "Running $name..."
    valgrind --leak-check=full \
             --xml=yes \
             --xml-file="$report_file" \
             "$file"

    echo "Report saved to $report_file"
    echo "-----------------------------------"

    ((counter++))
  fi
done

#generate the html report
python3 tools/valgrind-report-maker.py valgrind-reports -o docs/valgrind-report.html

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

#get rid of valgrind xml reports
rm -rf valgrind-reports
