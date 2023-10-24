cmake_minimum_required(VERSION 3.25)

include(FetchContent)
FetchContent_Declare(
    googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark
    GIT_TAG           main
)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(time_benchmark time_benchmark.cpp)

target_link_libraries(time_benchmark PUBLIC
    benchmark::benchmark
    tgcsa
    compact_suffix_array
    contact
    suffix
    bitvector
)