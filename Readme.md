# Dependencies
- g++ >= version 11.4.0
- cmake >= version 3.25
- googletest commit 8be20cce6931433c8bc3124beea91922cd621423 or later

# Enviroment
- [Visual Studio Code](https://code.visualstudio.com/)
- [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools)
- [CMake Test Explorer](https://marketplace.visualstudio.com/items?itemName=fredericbonnet.cmake-test-adapter)

# Running:

``` zsh
cmake -S . -B build
cmake --build build
cd build/src && ./main
```

# Testing

The unit tests for this project were implemented using [googletest](https://github.com/google/googletest)


Build and execute tests:

``` zsh
cmake -S . -B build
cmake --build build
cd build && ctest && cd .. 
```