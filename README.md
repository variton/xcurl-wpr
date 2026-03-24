# Xcurl-wpr - x curl wrapper
A cxx wrapper around curl.
it is intended to provide a simple interface c++ interface
to the curl library. 

## Clone repository
*remark:*
    *make sure your ssh key was added to you github account*

```
git clone git@github.com:variton/xcurl-wpr.git

```

## Environment to develop the xcurl-wpr
*remark:*
    *make sure you have the rights to pull the docker image*

```
docker pull ghcr.io/variton/icxx-resolute:1.0

```

## Create the docker container env to develop the xcurl-wpr

```
docker run --name=cxx-resolute --hostname=cypher -v $PWD:/home/cxx-core --net=host --restart=no -it icxx-resolute:1.0 /bin/bash

```

## Build & compile xcurl-wpr
in debug:

```
./build.sh debug

```
in release:

```
./build.sh release

```

### Use flags to trigger documentation generation and static analysis
*remark:*
    *the order for the flags are important still*

```
./build.sh <build_mode> -d -a

```

### Run the local CI

```
./local-ci.sh

```

## Install libxcwpr

## Generate the documentation
*remark:*
    *make sure to use the icxx-resolute:1.0 docker image*

Execute the following cli:

```
./build-doc.sh

```

## Description

### Dependencies
*This project has the following dependencies:*

#### Compiler

- gcc 15.2
- clang 21.1.8

#### Tools

- cmake 4.2.3
- ninja 1.13.2
- valgrind 3.26.0
- clang-tidy
- run-clang-tidy
- scan-build

#### Libraries

- spdlog [libspdlog1.15]
- doctest 0.24.2-1
- curl 8.18.0

### Documentation

- \ref design
- \ref docker
- \ref build
- \ref tests 
- \ref cli
