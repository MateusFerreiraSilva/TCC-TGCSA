#include <gtest/gtest.h>
#include "../src/tgcsa.h"

vector<Contact> contacts {
        Contact(1, 3, 1, 8),
        Contact(1, 4, 5, 8),
        Contact(2, 1, 1, 5),
        Contact(4, 3, 7, 8),
        Contact(4, 5, 5, 7)
};

TGCSA tgcsa(contacts);


TEST(TGCSATest, direct_neighbors_test) {
  
  vector<pair<uint, uint>> test_case_inputs {
    { 1, 5 },
    { 1, 6 },
    { 1, 7 },
    { 1, 8 },
    { 2, 3 },
    { 4, 6 }
  };
  vector<vector<uint>> test_cases_output {
    { 3, 4 },
    { 1 },
    { 5 }
  };

  for (uint i = 0; i < test_case_inputs.size(); i++) {
    vector<uint> neighbors = tgcsa.direct_neighbors(
      test_case_inputs[i].first,
      test_case_inputs[i].second
    );

    cout <<  "neighbors:" << endl;
    for (auto n : neighbors) {
      cout << n << " ";
    }
    cout << endl << endl;

    if (i < 3) {
      ASSERT_EQ(neighbors.size(), test_cases_output[0].size());
      for (uint j = 0; j < neighbors.size(); j++) {
        ASSERT_EQ(neighbors[j], test_cases_output[0][j]);
      }
    } else if (i == 3) {
      ASSERT_TRUE(neighbors.empty());
    } else if (i == 4) {
      ASSERT_EQ(neighbors.size(), test_cases_output[1].size());
      for (uint j = 0; j < neighbors.size(); j++) {
        ASSERT_EQ(neighbors[j], test_cases_output[1][j]);
      }
    } else if (i == 5) {
      ASSERT_EQ(neighbors.size(), test_cases_output[2].size());
      for (uint j = 0; j < neighbors.size(); j++) {
        ASSERT_EQ(neighbors[j], test_cases_output[2][j]);
      }
    }
  }
}

TEST(TGCSATest, reverse_neighbors_test) {
      vector<pair<uint, uint>> test_case_inputs {
    { 3, 7 },
    { 4, 6 },
  };
  vector<vector<uint>> test_cases_output {
    { 1, 4 },
    { 1 },
  };

  for (uint i = 0; i < test_case_inputs.size(); i++) {
    vector<uint> neighbors = tgcsa.reverse_neighbors(
      test_case_inputs[i].first,
      test_case_inputs[i].second
    );

    cout <<  "neighbors:" << endl;
    for (auto n : neighbors) {
      cout << n << " ";
    }
    cout << endl << endl;

    ASSERT_EQ(neighbors.size(), test_cases_output[i].size());
    for (uint j = 0; j < neighbors.size(); j++) {
        ASSERT_EQ(neighbors[j], test_cases_output[i][j]);
    }
  }
}