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

TEST(CompactSuffixArrayTests, AssertGapsValues) {
  vector<uint> expected_gaps_values { 0, 5, 10, 18 };

  vector<uint> gaps = csa.get_gaps(contacts);

  ASSERT_EQ(gaps.size(), CONTACT_LENGTH);
  ASSERT_EQ(gaps, expected_gaps_values);
}


TEST(CompactSuffixArrayTests, AssertSidValues) {

  vector<Contact> sigmaLine {
    Contact(1, 8, 11, 26),
    Contact(1, 9, 15, 26),
    Contact(2, 6, 11, 23),
    Contact(4, 8, 17, 26),
    Contact(4, 10, 15, 25)
  };

  vector<uint> expected_sid_values {
    1, 5, 8, 13, 1, 6, 9, 13, 2, 4, 8, 11, 3, 5, 10, 13, 3, 7, 9, 12
  };


  ASSERT_EQ(csa.get_sid(sigmaLine), expected_sid_values);
}


TEST(CompactSuffixArrayTests, AssertiCsaValues) {
  vector<uint> sid {
    1, 5, 8, 13, 1, 6, 9, 13, 2, 4, 8, 11, 3, 5, 10, 13, 3, 7, 9, 12
  };

  vector<uint> expectediCSAValues {
    1, 5, 9, 13, 17, 10, 2, 14, 6, 18, 11, 3, 19, 7, 15, 12, 20, 4, 8, 16
  };

  ASSERT_EQ(csa.get_iCSA(sid), expectediCSAValues);
}

TEST(CompactSuffixArrayTests, AssertPsiRegularValues) {
  vector<uint> iCSA {
    1, 5, 9, 13, 17, 10, 2, 14, 6, 18, 11, 3, 19, 7, 15, 12, 20, 4, 8, 16
  };
  
  vector<uint> expectedPsiRegularValues {
    7, 9, 6, 8, 10, 11, 12, 15, 14, 13, 16, 18, 17, 19, 20, 4, 1, 2, 3, 5
  };

  ASSERT_EQ(csa.get_psi_regular(iCSA), expectedPsiRegularValues);
}

TEST(CompactSuffixArrayTests, AssertPsiValues) {
  vector<uint> PsiRegular {
    7, 9, 6, 8, 10, 11, 12, 15, 14, 13, 16, 18, 17, 19, 20, 4, 1, 2, 3, 5
  };

  vector<uint> expectedPsiValues {
    7, 9, 6, 8, 10, 11, 12, 15, 14, 13, 16, 18, 17, 19, 20, 3, 5, 1, 2, 4
  };

  ASSERT_EQ(csa.get_psi(PsiRegular), expectedPsiValues);
}

TEST(CompactSuffixArrayTests, get_map_test) {
  vector<uint> original_sequence {
    1, 3, 1, 8, 1, 4, 5, 8, 2, 1, 1, 5, 4, 3, 7, 8, 4, 5, 5, 7 
  };

  vector<uint> sid_values {
    1, 5, 8, 13, 1, 6, 9, 13, 2, 4, 8, 11, 3, 5, 10, 13, 3, 7, 9, 12
  };

  ASSERT_EQ(original_sequence.size(), sid_values.size());

  for (uint i = 0; i < original_sequence.size(); i++) {
    uint get_map_response = csa.get_map(original_sequence[i], (ContactElementType)(i % CONTACT_LENGTH));
    ASSERT_EQ(get_map_response, sid_values[i]);
  }
}

TEST(CompactSuffixArrayTests, get_unmap_test) {
  vector<uint> sid_values {
    1, 5, 8, 13, 1, 6, 9, 13, 2, 4, 8, 11, 3, 5, 10, 13, 3, 7, 9, 12
  };

  vector<uint> original_sequence {
    1, 3, 1, 8, 1, 4, 5, 8, 2, 1, 1, 5, 4, 3, 7, 8, 4, 5, 5, 7 
  };

  ASSERT_EQ(original_sequence.size(), sid_values.size());

  for (uint i = 0; i < original_sequence.size(); i++) {
    uint get_unmap_response = csa.get_unmap(sid_values[i], (ContactElementType)(i % CONTACT_LENGTH));
    ASSERT_EQ(get_unmap_response, original_sequence[i]);
  }
}

TEST(CompactSuffixArrayTests, CSA_binary_search_test) {

  vector<pair<uint, uint>> test_cases {
    { 0, 1 },
    { 17, 19 },
    { 5, 5 }
  };

  // CSA_binary_search returns indexes in sid where it was found 

  ASSERT_EQ(csa.CSA_binary_search(csa.get_map(1, ContactElementType::SrcVertex)), test_cases[0]);
  ASSERT_EQ(csa.CSA_binary_search(csa.get_map(8, ContactElementType::EndingTime)), test_cases[1]);
  ASSERT_EQ(csa.CSA_binary_search(csa.get_map(1, ContactElementType::TargetVertex)), test_cases[2]);
}

TEST(CompactSuffixArrayTests, direct_neighbors_test) {
  vector<uint> test_cases { 3, 4 };

  // vector<uint> neighbors = csa.direct_neighbors(1, 6);
  vector<uint> neighbors = csa.direct_neighbors(1, 7); // works

  cout <<  "neighbors:" << endl;
  for (auto n : neighbors) {
    cout << n << endl;
  }
  cout << endl;

  // for (uint i = 0; i < neighbors.size(); i++) {
  //   neighbors[i] = csa.unmap_id();
  // }

  ASSERT_EQ(neighbors.size(), test_cases.size());
  for (uint i = 0; i < neighbors.size(); i++) {
    ASSERT_EQ(neighbors[i], test_cases[i]);
  }
}