cmake_minimum_required(VERSION 3.25)

add_library(contact contact.cpp contact.h)
add_library(bitvector bitvector.cpp bitvector.h)
add_library(compact_suffix_array compact_suffix_array.cpp compact_suffix_array.h)
add_library(tgcsa tgcsa.cpp tgcsa.h)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC
    tgcsa
    compact_suffix_array
    contact
    bitvector
)