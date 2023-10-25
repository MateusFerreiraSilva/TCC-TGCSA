cmake_minimum_required(VERSION 3.25)

add_library(contact contact.cpp contact.h)
add_library(suffix suffix.cpp suffix.h)
add_library(file_utils file_utils.cpp file_utils.h)
add_library(command_line_interface command_line_interface.cpp command_line_interface.h)

target_link_libraries(file_utils PUBLIC
    contact
)

target_link_libraries(command_line_interface PUBLIC
    tgcsa
    compact_suffix_array
    contact
    suffix
    bitvector
    file_utils
    uncompact_temporal_graph_adj_list
    uncompact_temporal_graph_edge_list
)