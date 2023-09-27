cmake_minimum_required(VERSION 3.25)

project(
    TCC
    VERSION 1.0
    LANGUAGES CXX
)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# adding flag -g to the compilation
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)