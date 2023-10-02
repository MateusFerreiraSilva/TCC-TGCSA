#ifndef BITVECTOR
#define BITVECTOR

#include <bits/stdc++.h>

using namespace std;

#define BITSET_MAX_SIZE_TEST 20
#define BITSET_MAX_SIZE 64

class Bitvector {
    private:
        // bitset<BITSET_MAX_SIZE_TEST> bs;
        bitset<BITSET_MAX_SIZE> bs;

        void validateIdx(uint idx);
        uint select(uint idx, uint type);

    public:
        void print();
        uint access(uint idx);
        void set(uint idx);
        void unset(uint idx);
        void flip(uint idx);
        uint rank1(uint idx);
        uint rank0(uint idx);
        uint select1(uint idx);
        uint select0(uint idx);
};

#endif