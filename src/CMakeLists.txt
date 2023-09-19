cmake_minimum_required(VERSION 3.27)

add_library(contact contact.cpp contact.h)
add_library(bitvector bitvector.cpp bitvector.h)
add_library(compact_suffix_array compact_suffix_array.cpp compact_suffix_array.h)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC
    compact_suffix_array
    contact
    bitvector
)