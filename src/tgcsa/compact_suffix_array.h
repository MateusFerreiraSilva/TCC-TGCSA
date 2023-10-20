#ifndef COMPACT_SUFFIX_ARRAY
#define COMPACT_SUFFIX_ARRAY

#include <bits/stdc++.h>
#include "../utils/contact.h"
#include "bitvector.h"

using namespace std;

enum class ContactElementType {
    SrcVertex,
    TargetVertex,
    StartingTime,
    EndingTime
};

class CompactSuffixArray {
    private:
        static uint mod(int a, int b);
        static vector<uint> get_gaps(const vector<Contact>& contacts);
        static vector<Contact>* get_sequence_with_offset(const vector<Contact>& contacts, const vector<uint>& gaps);
        vector<uint> get_S(const vector<uint>& sid);
        static Bitvector get_bitvector_B(const vector<Contact>& contacts);
        Bitvector get_bitvector_D(const vector<uint>& sid, const vector<uint>& A);
        uint map_id(uint symbol);
        uint unmap_id(uint id);
        static vector<pair<vector<uint>, uint>> get_suffixes_and_indexes(const vector<uint>& sequence);
        static vector<vector<uint>> get_suffixes(const vector<pair<vector<uint>, uint>>&  suffixes_and_indexes);
        pair<uint, uint> get_suffix_range(uint idx);

    public:
        vector<uint> gaps;
        Bitvector B;
        Bitvector D;
        // sort list of distinct symbols that occurs in the original sequence, see: Word-Based Self-Indexes for Natural Language Text
        vector<uint> S;
        vector<uint> psi;
        uint sequence_size;

        CompactSuffixArray(vector<Contact>& contacts, const bool debug_mode=false);
        vector<uint>* get_sid(const vector<Contact>& contacts_with_offset);
        static vector<uint>* get_iCSA(const vector<uint>& sequence);
        static vector<uint>* get_psi_regular(const vector<uint>& A);
        static vector<uint> get_psi(const vector<uint>& psi_reg);
        // map into final alphabet without holes
        uint get_map(uint symbol, ContactElementType type);
        // unmaps to the original alphabet
        uint get_unmap(uint id, ContactElementType type);
        // return the range (start, end) on the CSA where the symbol occurs
        pair<uint, uint> CSA_binary_search(uint id);
};

#endif