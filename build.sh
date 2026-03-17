#!/usr/bin/bash

BUILD_TYPE="Debug"
BUILD_DIR="build/debug"
ROOT_DIR=$PWD

if [[ "${1:-}" == "release" ]]; then
  BUILD_TYPE="Release"
  BUILD_DIR="build/release"
elif [[ "${1:-}" == "debug" ]]; then
  echo "Default build config"
elif [[ "${1:-}" == "clean-debug" ]]; then
  echo "Removing debug build"
  rm -rf build/debug
  rm -rf bin/*
  exit 1
elif [[ "${1:-}" == "clean-release" ]]; then
  echo "Removing release build"
  rm -rf build/release
  rm -rf bin/*
  exit 1
elif [[ "${1:-}" == "clean" ]]; then
  echo "Removing all builds"
  rm -rf build
  rm -rf bin/*
  exit 1
else
  echo "Missing build type"
  echo "Usage: $0 [release|debug|clean-release|clean-debug|clean"
  exit 1
fi

process_a=false
process_d=false

for arg in "$@"; do
  if [[ "$arg" == "-a" ]]; then
    process_a=true
    echo "Flag -a detected"
  fi

  if [[ "$arg" == "-d" ]]; then
    process_d=true
    echo "Flag -d detected"
  fi
done

mkdir -p "$BUILD_DIR"

echo "Setting up build config to $BUILD_TYPE"

cmake -S . \
  -B "$BUILD_DIR" \
  -G Ninja \
  -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
  -DCMAKE_CXX_COMPILER=g++-15 \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

echo "Finished $BUILD_TYPE configuration"

ninja -C "$BUILD_DIR" -j `nproc`

#launch unit tests
cd $BUILD_DIR

if [[ "${1:-}" == "release" ]]; then
  ctest --output-on-failure -j `nproc` 
else                                                                                                                                                                     
  ctest -V --output-on-failure -j `nproc`                                                                                                                        
fi 

#build documentation if flag -d selected
if $process_d; then
  cd $ROOT_DIR
  cmake -S . -B docs/build -G Ninja
  cmake --build docs/build --target doxygen > docs.log
fi

#run analysis if flag -a selected
if $process_a; then
  cd $ROOT_DIR
  run-clang-tidy -p "$BUILD_DIR" > clang.analysis
  scan-build --status-bugs cmake --build "$BUILD_DIR" -j `nproc`
fi
