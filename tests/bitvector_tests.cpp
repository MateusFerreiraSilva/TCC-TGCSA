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
    string expected_str = "011010101111000101000001011";
    string bitvector_str = csa.B.to_string();

    ASSERT_EQ(bitvector_str, expected_str);
}

TEST(BitvectorTests, BitvectorAccessTest) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.B.access(0), 0);
    ASSERT_EQ(csa.B.access(1), 1);
    ASSERT_EQ(csa.B.access(3), 0);
    ASSERT_EQ(csa.B.access(4), 1);
    ASSERT_EQ(csa.B.access(7), 0);
    ASSERT_EQ(csa.B.access(12), 0);
    ASSERT_EQ(csa.B.access(17), 1);
    ASSERT_EQ(csa.B.access(20), 0);
    ASSERT_EQ(csa.B.access(26), 1);
}

TEST(BitvectorTests, BitvectorRank1Test) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.B.rank1(1), 1);
    ASSERT_EQ(csa.B.rank1(2), 2);  
    ASSERT_EQ(csa.B.rank1(3), 2);
    ASSERT_EQ(csa.B.rank1(4), 3);

    ASSERT_EQ(csa.B.rank1(10), 7);
    ASSERT_EQ(csa.B.rank1(11), 8);

    ASSERT_EQ(csa.B.rank1(23), 11);
    ASSERT_EQ(csa.B.rank1(24), 11);
    ASSERT_EQ(csa.B.rank1(25), 12);
    ASSERT_EQ(csa.B.rank1(26), 13);
}

TEST(BitvectorTests, BitvectorRank0Test) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.B.rank0(0), 0); // this implementation have a "extra" space in the start of the B
    ASSERT_EQ(csa.B.rank0(1), 0); 

    ASSERT_EQ(csa.B.rank0(3), 1);
    ASSERT_EQ(csa.B.rank0(4), 1);

    ASSERT_EQ(csa.B.rank0(26), 13);
}

TEST(BitvectorTests, BitvectorSelect1Tests) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.B.select1(1), 1);
    ASSERT_EQ(csa.B.select1(4), 6);
    ASSERT_EQ(csa.B.select1(6), 9);
    ASSERT_EQ(csa.B.select1(9), 15);
    ASSERT_EQ(csa.B.select1(13), 26);
}

TEST(BitvectorTests, BitvectorSelect0Tests) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.B.select0(1), 0);
    ASSERT_EQ(csa.B.select0(2), 3);
    ASSERT_EQ(csa.B.select0(6), 13);
    ASSERT_EQ(csa.B.select0(11), 20);
    ASSERT_EQ(csa.B.select0(14), 24);
}

TEST(BitvectorTests, BitvectorDToStringTest) {
    string expected_str = "101101101110101111000";
    string bitvector_str = csa.D.to_string();

    ASSERT_EQ(bitvector_str, expected_str);
}

TEST(BitvectorTests, BitvectorDTests) {
    // test made according with the example on Fig 2

    ASSERT_EQ(csa.D.access(0), 1);
    ASSERT_EQ(csa.D.access(1), 0);
    ASSERT_EQ(csa.D.access(2), 1);
    ASSERT_EQ(csa.D.access(10), 1);
    ASSERT_EQ(csa.D.access(11), 0);
    ASSERT_EQ(csa.D.access(17), 1);
    ASSERT_EQ(csa.D.access(18), 0);
    ASSERT_EQ(csa.D.access(19), 0);

    ASSERT_EQ(csa.D.rank1(0), 1);
    ASSERT_EQ(csa.D.rank1(1), 1);  
    ASSERT_EQ(csa.D.rank1(10), 8);
    ASSERT_EQ(csa.D.rank1(19), 13);

    ASSERT_EQ(csa.D.select1(1), 0);
    ASSERT_EQ(csa.D.select1(2), 2);  
    ASSERT_EQ(csa.D.select1(8), 10);
    ASSERT_EQ(csa.D.select1(13), 17);
}