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
        vector<uint> gaps;
        vector<Contact> sigma;
        vector<Contact> sigmaLine;
        vector<pair<vector<uint>, uint>> suffixes_and_indexes; // TO DO remove
        vector<vector<uint>> suffixes; // TO DO remove
        vector<uint> PsiRegular;

        uint mod(int a, int b);
        void initialzeGapsArray(vector<Contact>& contacts);
        vector<Contact> addOffsetToTheSequence(vector<Contact> & contacts);
        void initializeBitvector(vector<Contact> & contacts);
        uint map_id(uint symbol);
        uint unmap_id(uint id);
        vector<pair<vector<uint>, uint>> get_suffixes_and_indexes(vector<uint> sequence);
        vector<vector<uint>> get_suffixes(vector<pair<vector<uint>, uint>>  suffixes_and_indexes);
        pair<uint, uint> get_suffix_range(uint idx);

    public:
        Bitvector* bitvector;
        // sequence of id without gaps in the alphabet, ids to sigma array
        vector<uint> sid;
        // iCSA of sid
        vector<uint> A;
        vector<uint> Psi;

        CompactSuffixArray(vector<Contact> & contacts);
        vector<uint> get_gaps(vector<Contact>& contacts);
        vector<uint> get_sid(vector<Contact> sigmaLine);
        vector<uint> get_iCSA(vector<uint> sequence);
        vector<uint> get_psi_regular(vector<uint> iCSA);
        vector<uint> get_psi(vector<uint> PsiRegular);
        // map into final alphabet without holes
        uint get_map(uint symbol, ContactElementType type);
        // unmaps to the original alphabet
        uint get_unmap(uint id, ContactElementType type);
        // return the range (start, end) on the CSA where the symbol occurs
        pair<uint, uint> CSA_binary_search(uint id);
        
        void print();
};

#endif