#ifndef BITVECTOR
#define BITVECTOR

#include <bits/stdc++.h>

using namespace std;

class Bitvector {
    private:
        vector<bool> bs;

        void validateIdx(uint idx);
        uint select(uint idx, uint type);

    public:
        Bitvector(unsigned long size);
        void print();
        string to_string();
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