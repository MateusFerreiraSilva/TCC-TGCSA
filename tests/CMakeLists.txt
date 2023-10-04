cmake_minimum_required(VERSION 3.25)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/8be20cce6931433c8bc3124beea91922cd621423.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(file_utils_tests file_utils_tests.cpp)

add_executable(contact_tests contact_tests.cpp)

add_executable(compact_suffix_array_tests compact_suffix_array_tests.cpp)

add_executable(bitvector_tests bitvector_tests.cpp)

add_executable(tgcsa_tests tgcsa_tests.cpp)

add_executable(temporal_graphs_tests temporal_graphs_tests.cpp)

target_link_libraries(file_utils_tests PUBLIC
  GTest::gtest_main
  file_utils
  data_generator
)

target_link_libraries(contact_tests PUBLIC
  GTest::gtest_main
  contact
)

target_link_libraries(compact_suffix_array_tests PUBLIC
  GTest::gtest_main
  compact_suffix_array
  contact
  bitvector
)

target_link_libraries(bitvector_tests PUBLIC
  GTest::gtest_main
  compact_suffix_array
  contact
  bitvector
)

target_link_libraries(tgcsa_tests PUBLIC
  GTest::gtest_main
  tgcsa
  compact_suffix_array
  contact
  bitvector
)

target_link_libraries(temporal_graphs_tests PUBLIC
  GTest::gtest_main
  tgcsa
  compact_suffix_array
  bitvector
  contact
  uncompact_temporal_graph_adj_list
  uncompact_temporal_graph_edge_list
  file_utils
)

# TO DO understand what means "PUBLIC" in the targtarget_link_libraries

include(GoogleTest)

gtest_discover_tests(file_utils_tests)
gtest_discover_tests(contact_tests)
gtest_discover_tests(bitvector_tests)
gtest_discover_tests(compact_suffix_array_tests)
gtest_discover_tests(tgcsa_tests)
gtest_discover_tests(temporal_graphs_tests)