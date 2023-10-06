#ifndef TGCSA_CLASS
#define TGCSA_CLASS

#include <bits/stdc++.h>
#include "compact_suffix_array.h"

using namespace std;

class TGCSA {
    private:
        CompactSuffixArray *csa;
    public:
        TGCSA(const vector<Contact>& contacts, const bool debug_mode=false);
        vector<uint> direct_neighbors(uint vrtx, uint time);
        vector<uint> reverse_neighbors(uint vrtx, uint time);
        vector<pair<uint, uint>> snapshot(uint time);
        void print();
};

#endif