#include <bits/stdc++.h>
#include "Bitvector.h"

using namespace std;

void testBitvector() {
    Bitvector bitvector;

    bitvector.set(0);
    bitvector.set(4);
    bitvector.flip(12);

    bitvector.print();

    printf("rank %u: %u\n", 4, bitvector.rank1(4));
    printf("rank %u: %u\n", 5, bitvector.rank1(5));
    printf("rank %u: %u\n", 12, bitvector.rank1(12));
    printf("rank %u: %u\n", 19, bitvector.rank1(19));

    printf("select %u: %u\n", 1, bitvector.select1(1));
    printf("select %u: %u\n", 2, bitvector.select1(2));
    printf("select %u: %u\n", 3, bitvector.select1(3));
}


int main() {
    testBitvector();

    return 0;
}