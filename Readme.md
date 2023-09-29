# Dependencies
- g++ >= version 11.4.0
- cmake >= version 3.25
- valgrind >= 3.18.1
- googletest commit 8be20cce6931433c8bc3124beea91922cd621423 or later
- google benchmark commit 7736df03049c362c7275f7573de6d6a685630e0a or later

# Enviroment
- [Visual Studio Code](https://code.visualstudio.com/)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- [CMake Test Explorer](https://marketplace.visualstudio.com/items?itemName=fredericbonnet.cmake-test-adapter)

# Building:

This project can be build with the following commands:

``` zsh
cmake -S . -B build
cmake --build build
```

## Running:

``` zsh
cd build/src && ./main
```

## Testing

The unit tests for this project were implemented using [googletest](https://github.com/google/googletest)

Running tests:

``` zsh
cd build && ctest && cd .. 
```

## Benchmarking

### Space Benchmark

The space benchmarks of this project were made with [valgrind](https://valgrind.org/)

``` zsh
valgrind --tool=massif ./build/src/main
```

### Time Benchmark

The time benchmarks of this project were made with [google benchmark](https://github.com/google/benchmark)

``` zsh
./build/benchmark/time_benchmark/time_benchmark
```