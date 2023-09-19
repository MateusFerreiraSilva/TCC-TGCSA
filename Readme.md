# Running:

``` zsh
cmake -S . -B build
cmake --build build
cd build/src && ./main
```

# Testing

This projects use [gtest with cmake](https://google.github.io/googletest/quickstart-cmake.html)


Build and execute test:

``` zsh
cmake -S . -B build
cmake --build build
cd build && ctest && cd .. 
```