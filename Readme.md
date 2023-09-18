# Running:

``` bash
$ cd src
$ make
$ ./a.out
```

# Testing

This projects use [gtest with cmake](https://google.github.io/googletest/quickstart-cmake.html)


Build and execute test:

``` bash
$ cd tests
$ cmake -S . -B build
$ cmake --build build
$ cd build && ctest && cd .. 
```