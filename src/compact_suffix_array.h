#ifndef COMPACT_SUFFIX_ARRAY
#define COMPACT_SUFFIX_ARRAY

#include <bits/stdc++.h>
#include "contact.h"
#include "bitvector.h"

using namespace std;

class CompactSuffixArray {
    private:
        vector<uint> gaps;
        vector<Contact> sigma;
        vector<Contact> sigmaLine;
        vector<pair<vector<uint>, uint>> suffixes_and_indexes; // TO DO remove
        vector<vector<uint>> suffixes; // TO DO remove
        vector<uint> sid;
        vector<uint> iCSA;
        vector<uint> PsiRegular;
        vector<uint> Psi;
        Bitvector bitvector;

        uint mod(int a, int b);
        void initialzeGapsArray(vector<Contact>& contacts);
        vector<Contact> addOffsetToTheSequence(vector<Contact> & contacts);
        void initializeBitvector(vector<Contact> & contacts);
        uint mapId(uint id);
        void initializesid();
        /* O^2 to build PSI, can i be better? */
        vector<pair<vector<uint>, uint>> get_suffixes_and_indexes(vector<uint> sequence);
        vector<vector<uint>> get_suffixes(vector<pair<vector<uint>, uint>>  suffixes_and_indexes);
        void buildPsiRegular() ;
        void buildPsi();
        void printSigma();
        void printSigmaLine();
        void printBitvector() ;
        void printSid();
        void printSuffixes();
        void printCSA();
        void printPsiRegular();
        void printPsi();

    public:
        CompactSuffixArray(vector<Contact> & contacts);
        vector<uint> get_gaps(vector<Contact>& contacts);
        vector<uint> get_sid(vector<Contact> sigmaLine);
        vector<uint> get_iCSA(vector<uint> sequence);
        vector<uint> get_psi_regular(vector<uint> iCSA);
        vector<uint> get_psi(vector<uint> PsiRegular);
        // map into final alphabet without holes
        uint get_map(uint symbol, unsigned char type);
        // unmaps to the original alphabet
        uint get_unmap(uint symbol, unsigned char type);
        
        void print();
};

#endif