#include <gtest/gtest.h>
#include "../src/tgcsa/bitvector.h"
#include "../src/tgcsa/compact_suffix_array.h"
#include <bits/stdc++.h>

using namespace std;

vector<Contact> contacts {
    Contact(1, 3, 1, 8),
    Contact(1, 4, 5, 8),
    Contact(2, 1, 1, 5),
    Contact(4, 3, 7, 8),
    Contact(4, 5, 5, 7)
};

CompactSuffixArray csa(contacts);

TEST(BitvectorTests, BitvectorToStringTest) {
    string expected_str = "110100000101000111101010110";
    string bitvector_str = csa.bitvector->to_string();

    ASSERT_EQ(bitvector_str, expected_str);
}

TEST(BitvectorTests, BitvectorAccessTest) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.bitvector->access(0), 0);
    ASSERT_EQ(csa.bitvector->access(1), 1);
    ASSERT_EQ(csa.bitvector->access(3), 0);
    ASSERT_EQ(csa.bitvector->access(4), 1);
    ASSERT_EQ(csa.bitvector->access(7), 0);
    ASSERT_EQ(csa.bitvector->access(12), 0);
    ASSERT_EQ(csa.bitvector->access(17), 1);
    ASSERT_EQ(csa.bitvector->access(20), 0);
    ASSERT_EQ(csa.bitvector->access(26), 1);
}

TEST(BitvectorTests, BitvectorRank1Test) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.bitvector->rank1(1), 1);
    ASSERT_EQ(csa.bitvector->rank1(2), 2);  
    ASSERT_EQ(csa.bitvector->rank1(3), 2);
    ASSERT_EQ(csa.bitvector->rank1(4), 3);

    ASSERT_EQ(csa.bitvector->rank1(10), 7);
    ASSERT_EQ(csa.bitvector->rank1(11), 8);

    ASSERT_EQ(csa.bitvector->rank1(23), 11);
    ASSERT_EQ(csa.bitvector->rank1(24), 11);
    ASSERT_EQ(csa.bitvector->rank1(25), 12);
    ASSERT_EQ(csa.bitvector->rank1(26), 13);
}

TEST(BitvectorTests, BitvectorRank0Test) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.bitvector->rank0(0), 0); // this implementation have a "extra" space in the start of the bitvector
    ASSERT_EQ(csa.bitvector->rank0(1), 0); 

    ASSERT_EQ(csa.bitvector->rank0(3), 1);
    ASSERT_EQ(csa.bitvector->rank0(4), 1);

    ASSERT_EQ(csa.bitvector->rank0(26), 13);
}

TEST(BitvectorTests, BitvectorSelect1Tests) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.bitvector->select1(1), 1);
    ASSERT_EQ(csa.bitvector->select1(4), 6);
    ASSERT_EQ(csa.bitvector->select1(6), 9);
    ASSERT_EQ(csa.bitvector->select1(9), 15);
    ASSERT_EQ(csa.bitvector->select1(13), 26);
}

TEST(BitvectorTests, BitvectorSelect0Tests) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.bitvector->select0(1), 0);
    ASSERT_EQ(csa.bitvector->select0(2), 3);
    ASSERT_EQ(csa.bitvector->select0(6), 13);
    ASSERT_EQ(csa.bitvector->select0(11), 20);
    ASSERT_EQ(csa.bitvector->select0(14), 24);
}