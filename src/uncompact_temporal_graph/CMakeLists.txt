cmake_minimum_required(VERSION 3.25)

add_library(uncompact_temporal_graph uncompact_temporal_graph.cpp uncompact_temporal_graph.h)

target_link_libraries(uncompact_temporal_graph PUBLIC
    contact
)