# Cli {#cli}

## Configure the build system manager

Configure in debug mode with GCC 15 (Manually)

```
 mkdir build
 cd build
 cmake -S src -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++-15
```

Configure in release mode with GCC 15 (Manually)

```
 mkdir build
 cd build
 cmake -S src -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=g++-15 
```

*remark: we use ninja with cmake*

## Compile projects

Compile in debug (Manually)

```
ninja -C build/debug -j `nproc`

```

Compile in release (Manually)

```
ninja -C build/release -j `nproc`

```
