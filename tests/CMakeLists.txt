cmake_minimum_required(VERSION 3.27)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/8be20cce6931433c8bc3124beea91922cd621423.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(contact_tests contact_tests.cpp)

add_executable(compact_suffix_array_tests compact_suffix_array_tests.cpp)

add_executable(tgcsa_tests tgcsa_tests.cpp)

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

target_link_libraries(tgcsa_tests PUBLIC
  GTest::gtest_main
  tgcsa
  compact_suffix_array
  contact
  bitvector
)

# TO DO understand what means "PUBLIC" in the targtarget_link_libraries

include(GoogleTest)

gtest_discover_tests(contact_tests)
gtest_discover_tests(compact_suffix_array_tests)
gtest_discover_tests(tgcsa_tests)