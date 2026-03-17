# Tests {#tests}

## Run quality tests
open a terminal and run the following command:
    
```
todo; describe the quality test with valgrind

```
## Run the coverage tests

## Run the performance tests

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
