cmake_minimum_required(VERSION 3.25)

add_subdirectory(tgcsa)
add_subdirectory(data_generator)
add_subdirectory(utils)
add_subdirectory(uncompact_temporal_graph)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC
    tgcsa
    compact_suffix_array
    contact
    suffix
    bitvector
    file_utils
    uncompact_temporal_graph_adj_list
    uncompact_temporal_graph_edge_list
    command_line_interface
)