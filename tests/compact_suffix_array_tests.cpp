#include <gtest/gtest.h>
#include "../src/compact_suffix_array.h"

vector<Contact> contacts {
        Contact(1, 3, 1, 8),
        Contact(1, 4, 5, 8),
        Contact(2, 1, 1, 5),
        Contact(4, 3, 7, 8),
        Contact(4, 5, 5, 7)
};

CompactSuffixArray csa(contacts);


TEST(CompactSuffixArrayTests, AssertiCsaValues) {

  vector<uint> sid {
    1, 5, 8, 13, 1, 6, 9, 13, 2, 4, 8, 11, 3, 5, 10, 13, 3, 7, 9, 12
  };

  vector<uint> expectediCSAValues {
    1, 5, 9, 13, 17, 10, 2, 14, 6, 18, 11, 3, 19, 7, 15, 12, 20, 4, 8, 16
  };

  vector<uint> iCSA = csa.get_iCSA(sid);

  EXPECT_EQ(iCSA, expectediCSAValues);
}

TEST(CompactSuffixArrayTests, AssertPsiRegularValues) {

  vector<uint> expectedPsiRegularValues {
    7, 9, 6, 8, 10, 11, 12, 15, 14, 13, 16, 18, 17, 19, 20, 4, 1, 2, 3, 5
  };

  EXPECT_EQ(csa.PsiRegular, expectedPsiRegularValues);
}

TEST(CompactSuffixArrayTests, AssertPsiValues) {

  vector<uint> expectedPsiValues {
    7, 9, 6, 8, 10, 11, 12, 15, 14, 13, 16, 18, 17, 19, 20, 3, 5, 1, 2, 4
  };

  EXPECT_EQ(csa.Psi, expectedPsiValues);
}