#include <gtest/gtest.h>
#include "../src/tgcsa/contact.h"

const Contact contact(1, 2, 3, 4);

// Demonstrate some basic assertions.
TEST(ContactTests, ContactAssertionTest) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}