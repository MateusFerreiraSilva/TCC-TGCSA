cmake_minimum_required(VERSION 3.25)

add_library(contact contact.cpp contact.h)
add_library(file_utils file_utils.cpp file_utils.h)

target_link_libraries(file_utils PUBLIC
    contact
)