cmake_minimum_required(VERSION 3.25)

project(
    TCC
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# adding flag -g and -DMEMORY_PROFILER to the compilation
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -DMEMORY_PROFILER")

enable_testing()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
add_definitions(-DCMAKE_EXPORT_COMPILE_COMMANDS=ON)

add_subdirectory(src)
add_subdirectory(tests)