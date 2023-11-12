cmake_minimum_required(VERSION 3.25)

add_library(data_generator data_generator.cpp data_generator.h)

add_executable(data_generator_cli data_generator_cli.cpp)

target_link_libraries(data_generator_cli PUBLIC
    data_generator
    file_utils
)