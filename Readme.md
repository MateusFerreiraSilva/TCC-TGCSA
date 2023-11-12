# Dependencies
- g++ >= version 11.4.0
- cmake >= version 3.25
- valgrind >= 3.18.1
- googletest commit 8be20cce6931433c8bc3124beea91922cd621423 or later

# Enviroment
- [Visual Studio Code](https://code.visualstudio.com/)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- [CMake Test Explorer](https://marketplace.visualstudio.com/items?itemName=fredericbonnet.cmake-test-adapter)

# Usage:

## Building:

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

### Generating random data for benchmark
After building the project, it is possible to run the data_generator_cli by executing the following command:"
``` zsh
./build/src/data_generator/data_generator_cli
```
After entering the desired parameters, two files will be created at the root of this project: random_contacts.csv and queries.txt.

The space benchmarks of this project were made with [valgrind](https://valgrind.org/) tool [massif](https://valgrind.org/docs/manual/ms-manual.html)

Running benchmark:
``` zsh
valgrind --tool=massif --time-unit=ms --massif-out-file=massif.output ./build/src/main
ms_print massif.output 
```

Run all benchmarks
``` zsh
zsh ./benchmark/space_benchmark.sh
```