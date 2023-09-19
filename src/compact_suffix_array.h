#ifndef COMPACT_SUFFIX_ARRAY
#define COMPACT_SUFFIX_ARRAY

#include <bits/stdc++.h>
#include "contact.h"
#include "bitvector.h"

using namespace std;

class CompactSuffixArray {
    private:
        uint mod(int a, int b);
        void initialzeGapsArray(vector<Contact>& contacts);
        vector<Contact> addOffsetToTheSequence(vector<Contact> & contacts);
        void initializeBitvector(vector<Contact> & contacts);
        uint mapId(uint id);
        void initializesid();
        void buildCSA();
        /* O^2 to build PSI, can i be better? */
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
        vector<uint> gaps = vector<uint>(CONTACT_LENGTH);
        vector<Contact> sigma;
        vector<Contact> sigmaLine;
        vector<uint> sid;
        vector<vector<uint>> suffixes;
        vector<uint> iCSA;
        vector<uint> PsiRegular;
        vector<uint> Psi;
        Bitvector bitvector;


        CompactSuffixArray(vector<Contact> & contacts);
        void print();
};

#endif