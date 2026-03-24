# Tests {#tests}

## Run quality tests
open a terminal & run the following command:

launch test_xcurl
```
valgrind --leak-check=full ./bin/test_xcurl

```

launch test_xcurl_global
```
valgrind --leak-check=full ./bin/test_xcurl_global

```

## Run the coverage tests

cd to the root folder of the project & run the following command:

```
cmake --build $BUILD_DIR --target coverage

```

## Run unit tests
run the following commands:

in debug:
    
```
cd build/debug;ctest --output-on-failure -j `nproc`

```
in release:
  
```
cd build/release;ctest --output-on-failure -j `nproc`

```
## Run the performance tests
