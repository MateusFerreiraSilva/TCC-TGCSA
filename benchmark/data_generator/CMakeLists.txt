cmake_minimum_required(VERSION 3.25)

add_library(data_generator data_generator.cpp data_generator.h)
add_library(file_utils file_utils.cpp file_utils.h)

add_executable(data_generator_ci data_generator_ci.cpp)

target_link_libraries(data_generator_ci PUBLIC
    data_generator
    file_utils
)