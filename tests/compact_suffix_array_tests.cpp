#include <gtest/gtest.h>
#include "../src/compact_suffix_array.h"

vector<Contact> contacts {
        Contact(1, 3, 1, 8),
        Contact(1, 4, 5, 8),
        Contact(2, 1, 1, 5),
        Contact(4, 3, 7, 8),
        Contact(4, 5, 5, 7)
};

// Demonstrate some basic assertions.
TEST(CompactSuffixArrayTests, AssertPsiValues) {
  const CompactSuffixArray csa(contacts);

  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}