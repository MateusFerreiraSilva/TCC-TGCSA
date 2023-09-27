#ifndef TGCSA_CLASS
#define TGCSA_CLASS

#include <bits/stdc++.h>
#include "compact_suffix_array.h"

using namespace std;

class TGCSA {
    private:
        CompactSuffixArray *csa;
    public:
        TGCSA(vector<Contact> & contacts);
        vector<uint> direct_neighbors(uint vrtx, uint time);
        vector<uint> reverse_neighbors(uint vrtx, uint time);
        bool active_edge(uint src_vrtx, uint target_vrtx, uint time); // TO DO implementation
        vector<pair<uint, uint>> snapshot(uint time);
};

#endif