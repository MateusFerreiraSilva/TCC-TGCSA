cmake_minimum_required(VERSION 3.25)

include(FetchContent)
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark
    GIT_TAG           main
)
FetchContent_MakeAvailable(googlebenchmark)

add_library(custom_memory_manager custom_memory_manager.h)

target_link_libraries(custom_memory_manager PUBLIC
    benchmark::benchmark
)

add_executable(main_benchmark main_benchmark.cpp)

target_link_libraries(main_benchmark PUBLIC
    benchmark::benchmark
    custom_memory_manager
    tgcsa
    compact_suffix_array
    contact
    bitvector
)